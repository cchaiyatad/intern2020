# VGG16-ssd on VIM3 NPU

This work is implement from [Single Shot MultiBox Detector Implementation in Pytorch](https://github.com/qfgaohao/pytorch-ssd)

## Example
![example](/docs/image/work2_output.jpg "example")

* The *blue* frame is the prediction on desktop pc
* The *pink* frame is the prediction on Khadas VIM3

## Set up

###Step 1: convert pth model to onnx
1.  Clone from this [link](https://github.com/qfgaohao/pytorch-ssd) 
2.  Apply `01_convert_onnx_get_prior.patch`
3.  Install pip package from `requirement.txt`
4.  Download [model](https://storage.googleapis.com/models-hao/vgg16-ssd-mp-0_7726.pth) and [label](https://storage.googleapis.com/models-hao/voc-model-labels.txt) then place in models folder
5.  Run `scipt.sh `

After finish this step you will get `vgg16-ssd.onnx` and `priors.txt`

### Step 2: port to camera
*I use ACUITY 5.7.0 and ovxlib 1.1.18 library so it may not work in the future*

1.  Follow this [link ](https://docs.khadas.com/vim3/HowToUseNpu.html)
2.  Copy `convertVGG` folder and place in `acuity-toolkit/conversion_scripts` folder
3.  Copy `data.txt` and `image.jpg` and place in `acuity-toolkit/conversion_scripts/data` folder
4.  Place `vgg16-ssd.onnx` form step 1 and place in `acuity-toolkit/conversion_scripts/model`
5.  run `0_import_vgg.sh` `1_quantize_model_vgg.sh` and `2_export_case_code_vgg.sh`

After finish this step you will get `nbg_unify_vgg` folder

### Step 3: make prior dat
1.  Edit `priors.txt` from **step 1** in the first row and last row to look the same as other rows
2.  Place `priors.txt` in `03_make_prior_dat`
3.  Run `01_clearFile.py` and `02_writeData.c`

After finish this step you will get `priors.dat`

#### Step 4:
This step is the code that modify from **step 2**

* `nbg_unify_vgg` folder has source code
* `vgg` folder has a code that already compile 
* use `run.sh` to run the code

#### Step 5:
*To run evaluate for VOC2007 dataset *

1.  Download dataset then place JPEGImages folder on the same directory as vgg folder of **step 4**
2.  Run `runEvaluation.sh` script this step will get output folder
3.  Clone from this [link](https://github.com/qfgaohao/pytorch-ssd)
4.  Apply `05_evaluation.patch`
5.  Copy `output` folder from **2**. and place on the same directory with script
6.  run `runEvaluation.sh`

## Output

| Average Precision Per-class          | Desktop | VIM3   |
|--------------------------------------|---------|--------|
| aeroplane                            | 0.8025  | 0.7827 |
| bicycle                              | 0.8300  | 0.7986 |
| bird                                 | 0.7577  | 0.7496 |
| boat                                 | 0.7045  | 0.6762 |
| bottle                               | 0.5159  | 0.4914 |
| bus                                  | 0.8358  | 0.8605 |
| car                                  | 0.8595  | 0.8610 |
| cat                                  | 0.8703  | 0.8067 |
| chair                                | 0.6175  | 0.5918 |
| cow                                  | 0.8077  | 0.8068 |
| diningtable                          | 0.7621  | 0.7464 |
| dog                                  | 0.8442  | 0.7888 |
| horse                                | 0.8692  | 0.8080 |
| motorbike                            | 0.8493  | 0.8022 |
| person                               | 0.7934  | 0.7660 |
| pottedplant                          | 0.5275  | 0.4839 |
| sheep                                | 0.7781  | 0.7628 |
| sofa                                 | 0.8029  | 0.7513 |
| train                                | 0.8704  | 0.8613 |
| tvmonitor                            | 0.7640  | 0.7369 |
| Average Precision Across All Classes | 0.7731  | 0.7467 |

![output](/docs/image/work2_graph1.png "output")
![output](/docs/image/work2_graph2.png "output")