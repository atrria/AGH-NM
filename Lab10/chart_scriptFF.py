import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results_f.txt"
data = np.loadtxt(file)

x=data[:,0]
y=data[:,1]

plt.plot(x, y)

plt.xlabel('x')
plt.grid(True)

plt.title(r'$f_1(x) \in <-1.5,1>$')

plt.savefig("chart_f.png")