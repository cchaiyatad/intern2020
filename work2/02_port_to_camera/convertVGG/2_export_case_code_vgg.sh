NAME=vgg
ACUITY_PATH=../../bin/

export_ovxlib=${ACUITY_PATH}ovxgenerator

$export_ovxlib \
    --model-input ${NAME}.json \
    --data-input ${NAME}.data \
    --reorder-channel '0 1 2' \
    --channel-mean-value '123 117 104 1' \
    --export-dtype quantized \
    --model-quantize ${NAME}.quantize \
    --optimize VIPNANOQI_PID0X88  \
    --viv-sdk ../../bin/vcmdtools \
    --pack-nbg-unify 

rm -rf *.h *.c .project .cproject *.vcxproj *.lib BUILD *.linux

mv ../*_nbg_unify nbg_unify_${NAME}

cd nbg_unify_${NAME}

mv network_binary.nb ${NAME}.nb