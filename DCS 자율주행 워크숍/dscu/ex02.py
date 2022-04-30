# ex02.py : 함수 Call Back을 통한 프로세싱, Sound Sensor ( 데시벨 값 X, ADC 값임 )

import sys # import whole file
from pop import SoundMeter # import a method or class from a file/folder


# defining a function on_sound()
def on_sound(rms, _):
    if 1000 <= rms < 2000:
        print("\nlevel1", rms)
    elif 2000 <= rms < 5000:
        print("\nlevel2", rms)
    elif rms >= 5000:
        print("\nlevel3", rms)
    else:
				# flush -> clear the buffer
				# sys.stderr = urgent I/O ... standard error
        print(".", end='', flush=True, file=sys.stderr)


# defining the main func = start point 
def main():  
    sm = SoundMeter() # multiprocessing object ; noise check from mic
    sm.setCallback(on_sound) # this method references on_sound function

    input()


# module name check -> don't start main() in case this module has imported
if __name__ == "__main__":
    main()