/*-------------------------------------------
                Includes
-------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vsi_nn_pub.h"

#include "vnn_global.h"
// #include "vnn_post_process.h"

#include "vgg_process.h"

#define _BASETSD_H

/*-------------------------------------------
                  Functions
-------------------------------------------*/
const u_int32_t TENSOR_SIZE = 8732;
const u_int8_t LABEL_CLASS_COUNT = 21; // 1 to 21

vsi_status getTensorData(vsi_nn_graph_t *graph, vsi_nn_tensor_t *tensor, int sz, float *buffer)
{
    vsi_status status = VSI_FAILURE;

    uint32_t stride;
    uint8_t *tensor_data = NULL;

    stride = vsi_nn_TypeGetBytes(tensor->attr.dtype.vx_type);

    tensor_data = (uint8_t *)vsi_nn_ConvertTensorToData(graph, tensor);

    for (int i = 0; i < sz; i++)
    {
        status = vsi_nn_DtypeToFloat32(&tensor_data[stride * i], &buffer[i], &tensor->attr.dtype);
    }

    TEST_CHECK_STATUS(status, final);

final:
    if (tensor_data)
        vsi_nn_Free(tensor_data);
    return VSI_SUCCESS;
}

//index 0: size
//index 1...TENSOR_SIZE index that score more than thershold
uint32_t *findScore(int index, float *bufferData, uint32_t sz, float threshold)
{
    uint32_t *indexData = NULL;
    indexData = (uint32_t *)malloc(sizeof(uint32_t) * (TENSOR_SIZE + 1));
    if (indexData == NULL)
    {
        return indexData; //For error handle
    }
    uint32_t count = 0;

    for (uint32_t i = index; i < sz; i += LABEL_CLASS_COUNT)
    {
        if (bufferData[i] >= threshold)
        {
            count++;
            indexData[count] = i;
        }
    }

    indexData[0] = count;
    return indexData;
}

//index [0..8732]
//return 1 if complete
//priorsData in form of (centerX, centerY, h, w)
int findPriorsData(int index, float *buffer, FILE *priorsDataFile)
{
    fseek(priorsDataFile, sizeof(float) * 4 * index, SEEK_SET);
    //if error return 0
    for (int i = 0; i < 4; i++)
    {
        fread(buffer + i, sizeof(float), 1, priorsDataFile);
    }
    rewind(priorsDataFile);
    return 1;
}

//index [0..8732]
//predictData = bufferBox
//From model output to box (x1, y1, x2, y2) where x1 < x2 and y1 < y2
//return 1 if complete
//convertFormula refer to convert_locations_to_box in github
//process
//predict -> (centerX, centerY, w, h)? -> (x1, y1, x2, y2)
int convertLocationToBox(int index, float *priorsData, float *predictData, float *buffer)
{
    float centerVariance = 0.1;
    float sizeVariance = 0.2;

    //process 1
    buffer[0] = predictData[index * 4] * centerVariance * priorsData[2] + priorsData[0];
    buffer[1] = predictData[index * 4 + 1] * centerVariance * priorsData[3] + priorsData[1];
    buffer[2] = exp(predictData[index * 4 + 2] * sizeVariance) * priorsData[2];
    buffer[3] = exp(predictData[index * 4 + 3] * sizeVariance) * priorsData[3];

    //process 2
    // float h = buffer[2];
    // float w = buffer[3];
    // buffer[2] = buffer[0] + (h / 2);
    // buffer[0] = buffer[0] - (h / 2);
    // buffer[3] = buffer[1] + (w / 2);
    // buffer[1] = buffer[1] - (w / 2);
    float w = buffer[2];
    float h = buffer[3];
    buffer[2] = buffer[0] + (w / 2);
    buffer[0] = buffer[0] - (w / 2);
    buffer[3] = buffer[1] + (h / 2);
    buffer[1] = buffer[1] - (h / 2);
    return 1;
}

vsi_status convertPredict(vsi_nn_graph_t *graph, char *priorPath, char *threshold)
{
    vsi_status status = VSI_FAILURE;
    FILE *priorsDataFile = fopen(priorPath, "rb");
    if (priorsDataFile == NULL)
    {
        printf("ERROR: .dat cannot open\n");
        TEST_CHECK_STATUS(status, final);
    }
    vsi_nn_tensor_t *scores = vsi_nn_GetTensor(graph, graph->output.tensors[0]);
    vsi_nn_tensor_t *boxes = vsi_nn_GetTensor(graph, graph->output.tensors[1]);

    float filter_threshold = atof(threshold);
    if(!(0 <= filter_threshold && filter_threshold <= 1)){
        printf("Threshold must be between 0 - 1\n");
        TEST_CHECK_STATUS(status, final);
    }

    uint32_t szScore = 1;
    uint32_t szBox = 1;
    float *bufferScore = NULL;
    float *bufferBox = NULL;

    for (int i = 0; i < scores->attr.dim_num; i++)
    {
        szScore *= scores->attr.size[i];
    }
    bufferScore = (float *)malloc(sizeof(float) * szScore);
    if (bufferScore == NULL)
    {
        printf("ERROR");
        TEST_CHECK_STATUS(status, final);
    }

    status = getTensorData(graph, scores, szScore, bufferScore);
    TEST_CHECK_STATUS(status, final);

    for (int i = 0; i < boxes->attr.dim_num; i++)
    {
        szBox *= boxes->attr.size[i];
    }
    bufferBox = (float *)malloc(sizeof(float) * szBox);
    if (bufferBox == NULL)
    {
        printf("ERROR");
        TEST_CHECK_STATUS(status, final);
    }

    status = getTensorData(graph, boxes, szBox, bufferBox);
    TEST_CHECK_STATUS(status, final);

    /////
    for (int i = 1; i < LABEL_CLASS_COUNT; i++)
    {
        uint32_t *indexData = findScore(i, bufferScore, szScore, filter_threshold);

        if (indexData[0] == 0)
        { //NOT FOUND
            free(indexData);
            continue;
        }

        printf("%d;", i);
        float priorData[4];
        float outputBox[4];
        for (int j = 1; j < indexData[0] + 1; j++)
        {

            printf("[%f", bufferScore[indexData[j]]);

            u_int32_t index = indexData[j] / 21; //[0..8732]

            if (findPriorsData(index, priorData, priorsDataFile) != 1)
            {
                printf("ERROR");
                TEST_CHECK_STATUS(status, final);
            }

            if (convertLocationToBox(index, priorData, bufferBox, outputBox) != 1)
            {
                printf("ERROR");
                TEST_CHECK_STATUS(status, final);
            }

            for (int k = 0; k < 4; k++)
            {
                printf(",%f", outputBox[k]);
            }
            printf("]:");
        }
        printf("\n");
        free(indexData);
        //nms
    }
    /////

final:
    if (bufferScore)
        free(bufferScore);
    if (bufferBox)
        free(bufferBox);
    if (priorsDataFile)
        free(priorsDataFile);
    return VSI_SUCCESS;
}
