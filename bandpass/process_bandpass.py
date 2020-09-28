import numpy as np
import numpy.fft as fft
import matplotlib
import matplotlib.pyplot as plt

font = {'size': 14}
matplotlib.rc('font', **font)

infiles = [np.loadtxt(f"./data/{i:06d}.csv", skiprows=1) for i in range(10)]

# DC signal
dc = np.array([i[3] for i in infiles])

# Mean signal
me = np.array([2*np.mean(i) for i in infiles])

# Bandpass filter
n = len(infiles[0])
l = int(n/2)
fr = [fft.fft(i) for i in infiles]
fr = [np.concatenate((
    [vf[0]],
    (vf[1:l]+vf[:l+1:-1]))) for vf in fr]
fr = np.array([4*abs(f[80])/n for f in fr])

fig, (ax1, ax2, ax3) = plt.subplots(nrows=3, sharex=True)
ax1.plot(dc[1::2], 'C0.', ms=4)
ax2.plot(me[1::2], 'C1.', ms=4)
ax3.plot(fr[1::2], 'C2.', ms=4)
fig.savefig('shift_time.png')
plt.show()

# vt = infiles[0][1:]
# vf = fft.fft(vt)
# dt = 0.001
# n = len(vt)
# # t = np.arange(0, n*dt, dt)
# f = fft.fftfreq(n=n, d=dt)
# # vf[0] = 0
# vf = fft.fftshift(vf)/n
# f = fft.fftshift(f)
# fig, ax = plt.subplots()
# ax.plot(f, abs(vf), ms=5)
# ax.set_xlim([-210, 210])
# plt.show()