# ex07 : 단순화된 차량 운행 커맨드 

# `steering` → 조향 장치, 차량에 따라 회전각이 달라지므로 비율로 표현하는 것
# 방향1 전진 → 중지 → 방향2 전진 ...
# 실제 차에서는 이런 식으로 하면 갑자기 후진 시 전복될 위험이 큼 !!

from pop import Pilot
from threading import Thread
import time


def on_drive(car):
    on_drive.is_stop = False
    on_drive.cmd = 0

    steering = 0 # changing direction
    speed = 50

    car.steering = steering
    car.setSpeed(speed)

    while not on_drive.is_stop:
        if on_drive.cmd == 1:
            car.forward()

        elif on_drive.cmd == 2: 
            car.backward()

        elif on_drive.cmd == 3: # steer to left
            steering -= 0.1
            # min value is -1.0
            steering = -1.0 if steering < -1.0 else steering
            car.steering = steering

        elif on_drive.cmd == 4: # steer to right 
            steering += 0.1
            # max value is -1.0
            steering = 1.0 if steering > 1.0 else steering
            car.steering = steering
            
        elif on_drive.cmd == 5: # increase speed
            speed += 5
            # max value is 99
            speed = 99 if speed >= 99 else speed
            car.setSpeed(speed)

        elif on_drive.cmd == 6: # decrease speed
            speed -= 5
            # min value is 20
            speed = 20 if speed < 20 else speed
            car.setSpeed(speed)
        
        print(steering, speed)

        on_drive.cmd = 0
        time.sleep(0.1)
    
    car.steering = 0
    car.stop()


def on_cmd():
    while True:
        on_drive.cmd = int(input())

        # stop the car 
        if on_drive.cmd > 6:
            on_drive.is_stop = True
            break


def main():  
    car = Pilot.AutoCar()

    # driving thread, input thread
    Thread(target=on_drive, args=(car, )).start()
    Thread(target=on_cmd).start()


if __name__ == "__main__":
    main()