#!/bin/bash

NAME=mobilenet_tf
ACUITY_PATH=../bin/


tensorzone=${ACUITY_PATH}tensorzonex


$tensorzone \
    --action inference \
    --source text \
    --source-file ./data/validation_tf.txt  \
    --channel-mean-value '128 128 128 128' \
    --model-input ${NAME}.json \
    --model-data ${NAME}.data \
    --dtype quantized


