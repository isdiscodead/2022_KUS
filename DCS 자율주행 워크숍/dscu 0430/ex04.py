# ex04.py : 초음파 센서 

from pop import Pilot
from threading import Thread
import time

# `클로저` → 경량 클래스 같은 느낌, 함수로 구현
# 초음파는 저속에서 사용, 즉 주차 등의 상황에서 사용됨 !!

def UltraSonic(car):
    # using ultrasonic sensor 
    car.setSensorStatus(ultrasonic=1, axis9=0)

    def close():
        car.setSensorStatus(ultrasonic=0)

    UltraSonic.close = close

    def _inner():
        return car.getUltrasonic()
    
    return _inner


def on_ultrasonic(car, us):
    while True:
        V = us()
        
        # close to other things 
        if V[0][0] <= 15 or V[1][0] <= 15:
            # alarm start 
            Thread(target=car.alarm, args=(4, 8, 1/4)).start()

        print(V) # Distance Vector 

        time.sleep(0.1)


def main():  
    car = Pilot.AutoCar()
    us = UltraSonic(car)
    
    t = Thread(target=on_ultrasonic, args=(car, us))
    t.daemon = True
    t.start()

    input()

    UltraSonic.close()


if __name__ == "__main__":
    main()