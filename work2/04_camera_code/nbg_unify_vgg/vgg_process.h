#ifndef _VGG_PROCESS_H_
#define _VGG_PROCESS_H_
#ifdef __cplusplus
extern "C"{
#endif

// vsi_status vnn_PostProcessVgg(vsi_nn_graph_t *graph);

vsi_status getTensorData(vsi_nn_graph_t *graph, vsi_nn_tensor_t *tensor, int sz, float *buffer);
uint32_t *findScore(int index, float *bufferData,uint32_t sz , float threshold);
int findPriorsData(int index, float *buffer, FILE *priorsDataFile);
int convertLocationToBox(int index,float *priorsData, float *predictData, float *buffer);
vsi_status convertPredict(vsi_nn_graph_t *graph, char *priorPath, char *threshold);

#ifdef __cplusplus
}
#endif
#endif
