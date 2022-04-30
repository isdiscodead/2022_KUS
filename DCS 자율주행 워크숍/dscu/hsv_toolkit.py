# hsv_toolkit.py : 영상 색상 처리 예제

# 값을 조절하여 영상 속에서 특정 HSV 색상을 마스킹해 찾아냄 → 차선 등의 객체 구분
# RGB는 조명에 민감하지만, HSV는 그렇지 X

import cv2
from pop import Camera
import numpy as np
import time

cap = Camera(640, 480)

cv2.namedWindow("HSV Toolkit")

cv2.createTrackbar("L - H", "HSV Toolkit", 0, 179, lambda x: x)
cv2.createTrackbar("L - S", "HSV Toolkit", 0, 255, lambda x: x)
cv2.createTrackbar("L - V", "HSV Toolkit", 0, 255, lambda x: x)
cv2.createTrackbar("U - H", "HSV Toolkit", 179, 179, lambda x: x)
cv2.createTrackbar("U - S", "HSV Toolkit", 255, 255, lambda x: x)
cv2.createTrackbar("U - V", "HSV Toolkit", 255, 255, lambda x: x)
 
while True:   
    frame = cap.value
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    l_h = cv2.getTrackbarPos("L - H", "HSV Toolkit")
    l_s = cv2.getTrackbarPos("L - S", "HSV Toolkit")
    l_v = cv2.getTrackbarPos("L - V", "HSV Toolkit")
    u_h = cv2.getTrackbarPos("U - H", "HSV Toolkit")
    u_s = cv2.getTrackbarPos("U - S", "HSV Toolkit")
    u_v = cv2.getTrackbarPos("U - V", "HSV Toolkit")
 
    lower_range = np.array([l_h, l_s, l_v])
    upper_range = np.array([u_h, u_s, u_v])
    mask = cv2.inRange(hsv, lower_range, upper_range) 
    res = cv2.bitwise_and(frame, frame, mask=mask)

    mask_3 = cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR)
  
    stacked = np.hstack((mask_3,frame,res))
    
    cv2.imshow('HSV Toolkit',cv2.resize(stacked,None,fx=0.8,fy=0.8))
    
    key = cv2.waitKey(1)
    if key == 27:
        break
    
    if key == ord('s'):
        
        thearray = [[l_h,l_s,l_v],[u_h, u_s, u_v]]
        print(thearray)
        
        np.save('hsv_value',thearray)
        break
    
cv2.destroyAllWindows()