# ex06.py : Lidar Sensor 

# 라이다에는 회전 모터가 존재
# 반사 각도에 따라 돌아오지 못하는 값이 존재함 !!
# 라이다 값을 통해 정밀한 지도를 그리는 것 → 한 번에 X, 누적 데이터 필요

from pop import Pilot
from pop import LiDAR
from threading import Thread
import time


def Lidar():
    lidar = LiDAR.Rplidar()
    lidar.connect()
    lidar.startMotor()
    
    def close():
        lidar.stopMotor()

    Lidar.close = close

    def _inner():
        # angle and scale 
        return lidar.getVectors()
    
    return _inner


def on_lidar(car, lidar):
    on_lidar.is_stop = False

    while not on_lidar.is_stop:
        V = lidar()
        
        for v in V:
            # 15 degree from left / right ( front )
            if v[0] >= 360 - 15 or v[0] <= 15:
                if v[1] <= 500: # closer than 50 cm
                    Thread(target=car.alarm, args=(4, 8, 1/4)).start()
                print(v[1])

        time.sleep(0.1)


def main():  
    car = Pilot.AutoCar()
    lidar = Lidar()

    t = Thread(target=on_lidar, args=(car, lidar))
    t.daemon = True
    t.start()

    input()

    on_lidar.is_stop = True
    Lidar.close()

if __name__ == "__main__":
    main()