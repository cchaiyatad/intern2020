# Detect human face and guess age and gender
This work is implement from [InsightFace: 2D and 3D Face Analysis Project](https://github.com/deepinsight/insightface)

## Example
![example](/docs/image/work0_output.jpg "example")

## Set up
1.  Install CUDA
2.  Install MXNet with GPU support
3.  Type make to build cxx tools
4.  Install pip package from package.txt
5.  Download [RetinaFace-R50](https://www.dropbox.com/s/53ftnlarhyrpkg2/retinaface-R50.zip?dl=0) pretrained model and place both files in folder model
6.  From [insightface/gender-age/model/](https://github.com/deepinsight/insightface/tree/master/gender-age/model) download both file and place in folder model
7.  For image run `$ python imageDetect.py`
    For video run `$ python videoDetect.py`