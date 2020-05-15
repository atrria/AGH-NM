import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results3.txt"
data = np.loadtxt(file)

x=data[:,0]
y=data[:,1:5]
#y=data

#plt.plot(x,y[:,5], marker=".")
#plt.plot(x,y[:,6], marker=".")
for n in np.arange(0,4):
	plt.plot(x, y[:,n], marker=".")

plt.xlabel('iteracja')
plt.grid(True)

plt.legend([r'$x_1$', r'$x_2$', r'$x_3$', r'$x_m$'])
#plt.legend([r'$F[x_1,x_2]$', r'$F[x_1,x_2,x_3]$'])
plt.title(r'$x_1=1.5, f_2(x)$')

plt.savefig("chart3.png")