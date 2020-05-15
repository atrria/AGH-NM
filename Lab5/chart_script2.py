import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results.txt"
data = np.loadtxt(file)

nr_iter = data[7:, 0]
l = data[7:, 2]

plt.plot(nr_iter, l, color='orange', linewidth='2', marker='.', markersize='8')

plt.axis([0,11,0,0.31])
plt.legend([r'$\lambda_0$'], loc=4)
plt.xlabel('numer iteracji')
plt.ylabel(r'$\lambda$')
plt.grid(True)

plt.savefig("chart_a.png")

