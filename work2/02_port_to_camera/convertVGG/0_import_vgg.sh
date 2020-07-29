NAME=vgg
ACUITY_PATH=../../bin/

convert_onnx=${ACUITY_PATH}convertonnx

echo "convert_onnx vgg"
$convert_onnx \
   --onnx-model  ../model/vgg16-ssd.onnx \
   --net-output ${NAME}.json \
   --data-output ${NAME}.data 
