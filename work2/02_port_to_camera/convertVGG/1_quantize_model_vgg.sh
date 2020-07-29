NAME=vgg
ACUITY_PATH=../../bin/

tensorzone=${ACUITY_PATH}tensorzonex

#asymmetric_quantized-u8 dynamic_fixed_point-8 dynamic_fixed_point-16
$tensorzone \
    --action quantization \
    --source text \
    --source-file ../data/data.txt \
    --channel-mean-value '123 117 104 1' \
    --model-input ${NAME}.json \
    --model-data ${NAME}.data \
    --quantized-dtype asymmetric_quantized-u8 \
    --quantized-rebuild

$tensorzone \
    --action inference \
    --source text \
    --source-file ../data/data.txt \
    --channel-mean-value '123 117 104 1' \
    --model-input ${NAME}.json \
    --model-data ${NAME}.data \
    --dtype quantized