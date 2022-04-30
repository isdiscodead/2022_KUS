# ex01.py : 음악 재생

# import libraries 
from multiprocessing import Process
from playsound import playsound # third-party ... sudo pip3 install playsound-1.3.0.tar.gz 

# Volume -> pactl set-sink-volume @DEFAULT_SINK@ 150%

# 선택 제어 구조인 `if`, 반복 제어 구조인 `for`
# 멀티 프로세싱 하려면 p 객체를 여러 개 만들면 됨 !

# in the main process ... 
if False: # Change to True - False to test
    playsound("StairwayToHeaven.mp3")   

elif True: #  # multi processing
    pid_list = []

    for f in ["tetris-1.mp3", "tetris-2.mp3", "tetris-3.mp3", "tetris-4.mp3", "tetris-5.mp3"]:
        p = Process( target=playsound, args=(f,) )
        p.start()
        pid_list.append(p) # append to list 

    input("press ENTER to stop playback") # press enter in terminal to stop all music
    for p in pid_list :
        p.terminate() # forced terminate
    
else:
    for f in ["tetris-1.mp3", "tetris-2.mp3", "tetris-3.mp3", "tetris-4.mp3", "tetris-5.mp3"]:
        # target = method -> copy to process object p, args = args for method
        p = Process( target=playsound, args=(f,) )
        p.start()
        input("press ENTER to stop playback") # press enter in terminal to next music
        p.terminate() # forced terminate