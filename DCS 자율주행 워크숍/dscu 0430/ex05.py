# ex05.py : 마그네틱, 가속도, 자이로 센서 → axis9

# `가속도 센서`: 앞뒤가 y, 좌우가 x, 위아래 z축 → 이 값의 급격한 변화 감지 ( 충격, 전복 )
# `Gyro 센서` → 회전 ( 곡선 주행 흐름 감지 )


from pop import Pilot
from threading import Thread
import time

def IMU(car):
    car.setSensorStatus(ultrasonic=0, axis9=1)

    def close():
        car.setSensorStatus(axis9=0)

    IMU.close = close

    def _inner():
        # tuple return 
        return (car.getAccel(), car.getGyro())
    
    return _inner


def on_imu(car, imu):
    while True:
        V = imu() # two list 

        # use absolute value, -+ indicates direction
        a_x, a_y, a_z = [abs(v) for v in V[0]] # comprehension

        # compare with hyper parameter 
        # z = 9.8 -> gravitational acceleration
        if a_x > 0.5 or a_y > 1.0 or a_z < 9.0 or a_z > 10.0:
            # running while alarming -> using thead
            Thread(target=car.alarm, args=(4, 8, 1/4)).start()

        print(a_x, a_y, a_z)

        time.sleep(0.1)


def main():  
    car = Pilot.AutoCar()
    imu = IMU(car)

    t = Thread(target=on_imu, args=(car, imu))
    t.daemon = True
    t.start()

    input()

    IMU.close()

if __name__ == "__main__":
    main()