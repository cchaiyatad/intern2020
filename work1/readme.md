# Human pose estimation 
This work is implement from [Fast Human Pose Estimation CVPR2019](https://github.com/ilovepose/fast-human-pose-estimation.pytorch) and [Single Shot MultiBox Detector Implementation in Pytorch](https://github.com/qfgaohao/pytorch-ssd)

## Example
[video](https://youtu.be/Rv3ZJqK2-Ew)
![example](/docs/image/work1_output.jpg "example")


## Set up
1.  Clone from this [link](https://github.com/ilovepose/fast-human-pose-estimation.pytorch)
2.  Patch `fast_human_pose.patch`
3.  pip install package in requirements
4.  Download `hourglass_student_FPD.pth` from github 3.1 MPII dataset
5.  Download [model](https://storage.googleapis.com/models-hao/vgg16-ssd-mp-0_7726.pth)
6.  Create folder models and place the model in folder to look like this 
```models
├── detectPerson
│   ├── vgg16-ssd-mp-0_7726.pth
└── student_FPD
    └── hourglass_student_FPD.pth
```
7.  Make libs in the lib folder
8.  To use `run.sh` to run script and runEvaluation.sh to evaluate

## Output

| Model                   | r ankle | r knee | r hip | l hip | l knee | l ankle | pelvis | thorax | upper neck | head top | r wrist | r elbow | r shoulder | l shoulder | l elbow | l wrist | AVG   |
|-------------------------|---------|--------|-------|-------|--------|---------|--------|--------|------------|----------|---------|---------|------------|------------|---------|---------|-------|
| VGG16-SSD               | 65.9    | 69.65  | 75.98 | 76.48 | 70.53  | 65.95   | 78.54  | 83.08  | 83.53      | 83.15    | 73.13   | 76.36   | 80.87      | 80.63      | 75.92   | 72.16   | 75.41 |
| MobileNetV2 SSD         | 59.51   | 64.57  | 70.95 | 70.17 | 64.67  | 59.59   | 72.56  | 76.5   | 76.71      | 76.4     | 68.56   | 70.77   | 74.49      | 74.45      | 70.26   | 67.15   | 69.83 |
| fasterrcnn resnet50 fpn | 76.68   | 80.29  | 86.35 | 85.97 | 80.24  | 76.83   | 88.83  | 92.8   | 92.77      | 92.43    | 81.49   | 84.22   | 89.77      | 90.45      | 85.08   | 80.88   | 85.32 |

![output](/docs/image/work1_graph1.png "output")
![output](/docs/image/work1_graph2.png "output")
![output](/docs/image/work1_graph3.png "output")