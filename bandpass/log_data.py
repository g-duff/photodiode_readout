import serial
import numpy as np
from datetime import datetime


ser = serial.Serial('/dev/cu.usbmodem14301', timeout=3, baudrate=115200)
# ser = serial.Serial('COM5', timeout=3, baudrate=115200)
i = 0

while True:
    l = ser.readline()
    l = l.decode().split(' ')
    now = datetime.now()
    decoded = np.array(l[:-1], dtype=np.float)
    np.savetxt(f'./data/{i:06d}.csv', decoded, header=str(datetime.now().time()))
    print(i)
    i += 1
