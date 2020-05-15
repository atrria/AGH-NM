import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results_101.txt"
file2 = "results2_101.txt"
data = np.loadtxt(file)
data2 = np.loadtxt(file2)

x=data[:,0]
y=data[:,1]
x2=data2[:,0]
y2=data2[:,1]

plt.plot(x2, y2, color='black', linewidth=5)
plt.plot(x, y, color='orange', linewidth=1)

plt.xlabel('x')
plt.grid(True)
plt.legend(['g(x)', 'G(x)'])

plt.savefig("chart101.png")