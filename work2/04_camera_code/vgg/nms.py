def area(box):
    return max(0, (box[3] - box[1]) * (box[4] - box[2])) # return h * w and ensure that will not less than 0


def iou_of(box1, box2):
    area1 = area(box1)
    area2 = area(box2)

    xLeft      = max(box1[1], box2[1])
    yTop       = max(box1[2], box2[2])
    xRight     = min(box1[3], box2[3])
    yBottom    = min(box1[4], box2[4])

    if xLeft > xRight or yTop > yBottom: #not intersect
        return 0

    intersectArea = (xRight - xLeft) * (yBottom - yTop)
    return intersectArea / (area1 + area2 - intersectArea)



def nms(boxes, iou_threshold, width, height):
    output = []
    while len(boxes) > 0:
        boxes.sort()
        boxes = boxes[::-1]
        output.append(boxes[0])
        boxes = [box for box in boxes[1:] if iou_of(output[-1], box) < iou_threshold]
        
        output[-1][1] *= width
        output[-1][3] *= width
        output[-1][2] *= height
        output[-1][4] *= height

    return output


# get width and height
# File in format w,h
fileSizePath = "tmp/wh"
width = 1
height = 1
with open(fileSizePath) as wh:
    width, height = map(int, wh.readline().strip().split(","))

# File in format lable;[prob1,x11,y11,x21,y21]:[prob2,x12,y12,x22,y22]: where x1n < x2n and y1n < y2n
fileDataPath = "tmp/tmp"
iou_threshold = 0.45
output = []  # return in format [[label, [[prob, x11, y11, x21, y21],......]],[label2,.....]
with open(fileDataPath, "r") as data:
    for line in data.readlines():
        line = line.strip()[:-1]  # remove the :
        label, boxes = line.split(";")  # split ; to get lable
        boxes = [eval(box) for box in boxes.split(":")]
        output.append([label, nms(boxes, iou_threshold, width, height)])

print(output)
