import serial
import matplotlib.pyplot as plt
import numpy as np

ser = serial.Serial('COM5', timeout=3, baudrate=115200)
i = 0

while True:
    l = ser.readline()
    l = l.decode().split(' ')
    decoded = np.array(l[:-1], dtype=np.float)
    np.savetxt(f'./data/{i}.csv', decoded)
    i += 1
    print(i)
