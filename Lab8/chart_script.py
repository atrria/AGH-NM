import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results_2_14.txt"
file2 = "results_nods_2_14.txt"
data = np.loadtxt(file)
data2 = np.loadtxt(file2)

x=data[:,0]
y=data[:,1]
f=data[:,2]
xn=data2[:,0]
nods=data2[:,1]

plt.plot(x,y)
plt.plot(x,f, color='black')

plt.plot(xn,nods, linestyle='', color='#104176', marker='.', markersize=12)
plt.xlabel('x')
plt.grid(True)
plt.legend(['n=14', 'f(x)'])

plt.savefig("chart_2_14.png")
