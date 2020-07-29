/****************************************************************************
*   Generated by ACUITY 5.7.0
*   Match ovxlib 1.1.18
*
*   Neural Network appliction network definition header file
****************************************************************************/

#ifndef _VNN_VGG_H
#define _VNN_VGG_H
#ifdef __cplusplus
extern "C"{
#endif

#include "vsi_nn_pub.h"

#define VNN_APP_DEBUG (FALSE)
#define VNN_VERSION_MAJOR 1
#define VNN_VERSION_MINOR 1
#define VNN_VERSION_PATCH 18
#define VNN_RUNTIME_VERSION \
    (VNN_VERSION_MAJOR * 10000 + VNN_VERSION_MINOR * 100 + VNN_VERSION_PATCH)

_version_assert(VNN_RUNTIME_VERSION <= VSI_NN_VERSION,
                CASE_VERSION_is_higher_than_OVXLIB_VERSION)

void vnn_ReleaseVgg
    (
    vsi_nn_graph_t * graph,
    vsi_bool release_ctx
    );

vsi_nn_graph_t * vnn_CreateVgg
    (
    const char * data_file_name,
    vsi_nn_context_t in_ctx
    );

#ifdef __cplusplus
}
#endif

#endif
