# ex03.py : Threading, Camera Light Sensing 

from pop import Pilot
from threading import Thread
import time


def Light(car): # nested function -> lighter than class 
    # using cds sensor
    car.setSensorStatus(ultrasonic=0, axis9=0, cds=1)

    def close():
        car.setSensorStatus(cds=0)

    # redifine function as variable 
    Light.close = close

    def _inner():
        return car.getLight() # returning function of outside ( closer ... ? )
    
    return _inner # returning function's location


# turn on/off lamp according to light's ADC value
def on_light(car, light, limit_h, limit_l): 
    while True:
        l = light()

        # turn off the Lamp ( Front, Back )
        if l >= limit_h:
            car.setLamp(0, 0)

        # turn on the Lamp ( Front, Back )
        elif l <= limit_l:
            car.setLamp(1, 1)

        print("Light:", l)    
        time.sleep(0.1) # 


def main():  
    car = Pilot.AutoCar()
    light = Light(car) # return value of inner() ; location of car.getLight()
    
    # 1200~1100 -> stabilize value ; Schmitt Trigger
    t = Thread(target=on_light, args=(car, light, 1200, 1100)) 
    
    t.daemon = True
    t.start()

    input()

    Light.close()


if __name__ == "__main__":
    main()

# 자동차 프로그래밍에서는 cam 프로토콜 사용
# analog 값은 불안정하므로 데이터 전처리 필요 → `과적합 해소 코드` ; **Schmitt Trigger**
# → 경계 값인 1100 ~ 1200일 때는 아무것도 안 하는 이유 ...