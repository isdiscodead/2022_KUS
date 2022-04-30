# ex08.py :  카메라 영상 처리 

# 해당 예제 실행 시 `vcxsrv` 필요 → 윈도우 용 linux 서버 v program 시뮬레이터
    # 프로그램 실행 후 Disable access control 설정 필수 !!
    # 백그라운드에서 실행되는 것 확인
    # `DISPLAY = 192.168.55.100:0.0 python3 ex08.py` → 0.0 = 가상 모니터

import cv2
from pop import Camera

def main():
    window_title = "CSI Camera"

    # inform of captured pic
    # ndarray ; can calculated in only CPU
    cap = Camera(640, 480)
    
    while True:
        # an image of video = a frame 
        frame = cap.value
        
        # open a preview window 
        cv2.imshow(window_title, frame)

        # needs extra works 

        # quit menu
        keyCode = cv2.waitKey(10) & 0xFF
        if keyCode == 27 or keyCode == ord('q'): # change to ASCII code 
            break
        
    cv2.destroyAllWindows() # close the window

if __name__ == "__main__":
    main()