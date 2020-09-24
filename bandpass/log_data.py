import serial
import matplotlib.pyplot as plt
import numpy as np


ser = serial.Serial('COM3', timeout=1, baudrate=115200)
i = 0

while True:
    l = ser.readline()
    np.savetxt(l.decode(), f'{i}.csv')
    i += 1
