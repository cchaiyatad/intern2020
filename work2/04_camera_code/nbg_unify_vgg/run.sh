if [ $# -eq 2 ]
  then
    mkdir tmp
    identify -format %w,%h $1 > tmp/wh && \
    convert -colorspace sRGB -type truecolor -resize 300X300! $1 tmp/img.jpg && \
    bin_r/vgg vgg.nb priors.dat $2 tmp/img.jpg > tmp/tmp && \
    python nms.py
    rm -r tmp
else
    echo "Usage: ./run.sh [jpg image path] [threshold]"
fi


