import serial
import matplotlib.pyplot as plt
import numpy as np

def decode_input(line, l=4):
    ''' Return line as numpy array
    Returns array of zeros if impossible'''
    decoded = line.decode().split(' ')
    try:
        decoded = np.array(decoded, dtype=np.float)
    except:
        decoded = np.zeros(l)
    return decoded

# Log parameters
trace_length = 200
repeats = 10
ser = serial.Serial('COM3', timeout=1)

# Initialize coms and data
T = [i for i in range(trace_length)]
s = np.zeros(trace_length)

# Initialize figure
fig, ax = plt.subplots()
ax.set_xlim(0, trace_length)
ax.set_ylim(0, 1000)
trace, = ax.plot(T, s, color='k')
cursor, = ax.plot(0, 0, 'C3o')
cl = ax.axvline(0, color='k', ls='--')
ax.grid(True, which='major')

plt.show(block=False)

for r in range(repeats):
    for t in T:

        # Measure
        line = decode_input(ser.readline())
        s[t] = line[2]

        # Update plot
        trace.set_ydata(s)
        cursor.set_data(t, line[2])
        cl.set_xdata(t)
        plt.pause(0.01)
        # ax.draw_artist(trace)

ser.close()