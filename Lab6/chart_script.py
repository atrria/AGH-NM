import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results_z1.txt" #"results_z2.txt"
data = np.loadtxt(file)

real=data[:,0]
imag=data[:,1]
colors = ['gray', 'green', 'maroon', 'orange']
n=21

for i in np.arange(0,4):
    plt.plot(real[i*n:i*n+n-1], imag[i*n:i*n+n-1], colors[i], marker='.')

plt.axis([-2.3,4.3,-3.3,1.3]) #([-10.4,4.4,-10.4,1.8])
plt.legend([r'$z^{(0)}$', r'$z^{(1)}$', r'$z^{(2)}$', r'$z^{(3)}$'], loc=4)
plt.xlabel('Re(z)')
plt.ylabel('Im(z)')
plt.grid(True)
#plt.show()
plt.savefig("chart_z1.png") #_z2.png")


