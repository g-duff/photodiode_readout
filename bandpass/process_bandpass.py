import matplotlib.pyplot as plt
import numpy as np
import numpy.fft as fft

fname = '499'
infile = np.loadtxt(f'./{fname}.csv')

for i in range((infile.shape)[0]):
    vt = infile[i,:]
    vf = fft.fft(vt)

    dt = 0.002
    n = len(vt)

    # t = np.arange(0, n*dt, dt)
    f = fft.fftfreq(n=n, d=dt)
    # vf[0] = 0

    vf = fft.fftshift(vf)/n
    f = fft.fftshift(f)

    fig, ax = plt.subplots()
    ax.plot(f, abs(vf), ms=5)
    ax.set_xlim([-210, 210])
    plt.show()
    # fig.savefig(f'{fname}_{i}.png')
    # plt.close('all')