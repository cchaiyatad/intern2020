import cv2
import sys
import numpy as np
import datetime
import os
import glob

imageName = input('image source: ')

from retinaface import RetinaFace
import ageGender


thresh = 0.8
scales = [1024, 1980]

count = 1

gpuid = 0
detector = RetinaFace('./model/R50', 0, gpuid, 'net3')

# img = cv2.imread('t1.jpg')
img = cv2.imread(imageName)
im_shape = img.shape
target_size = scales[0]
max_size = scales[1]
im_size_min = np.min(im_shape[0:2])
im_size_max = np.max(im_shape[0:2])

im_scale = float(target_size) / float(im_size_min)
if np.round(im_scale * im_size_max) > max_size:
    im_scale = float(max_size) / float(im_size_max)

scales = [im_scale]
flip = False

for c in range(count):
  faces, landmarks = detector.detect(img, thresh, scales=scales, do_flip=flip)
  # print(c, faces.shape, landmarks.shape)

if faces is not None:
  # print('find', faces.shape[0], 'faces')
  for i in range(faces.shape[0]):
    box = faces[i].astype(np.int)
    color = (0,0,255)
    cv2.rectangle(img, (box[0], box[1]), (box[2], box[3]), color, 2)
#custom
    crop_img = img[box[1]:box[3], box[0]:box[2]]
    # cv2.imshow("test",crop_img)
    # cv2.waitKey(0)
    text = "Unknown"
    genderAge = ageGender.findAgeGender(crop_img)
    if(genderAge is not None):
	    gender, age = genderAge
	    text = "Male" if gender else "Female"
	    text += " age: " + str(age)
    cv2.putText(img, text, (box[0] - 5, box[1] - 5), cv2.FONT_HERSHEY_DUPLEX, 1.0, color, 1)

    if landmarks is not None:
      landmark5 = landmarks[i].astype(np.int)
      #print(landmark.shape)
      for l in range(landmark5.shape[0]):
        color = (0,0,255)
        if l==0 or l==3:
          color = (0,255,0)
        cv2.circle(img, (landmark5[l][0], landmark5[l][1]), 1, color, 2)

  #filename = './detector_test.jpg'
  # filename = 'output_' + imageName
  # print('writing', filename)
  cv2.imwrite("output.jpg", img)
  # cv2.imwrite("t.jpg", img)

