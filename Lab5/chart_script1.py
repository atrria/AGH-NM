import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results.txt"
data = np.loadtxt(file)

nr_iter = data[7:, 0]
l = data[7:, 2:]
colors = ['orange', 'purple', 'grey', 'green', 'red', 'blue']

for i in np.arange(0,6):
        plt.plot(nr_iter, l[:, i], colors[i], linewidth='2', marker='.', markersize='9')

plt.axis([0,11,0,0.6])
plt.legend([r'$\lambda_1$', r'$\lambda_2$', r'$\lambda_3$', r'$\lambda_4$', r'$\lambda_5$', r'$\lambda_6$'], loc=2) # legenda
plt.xlabel('numer iteracji')
plt.ylabel(r'$\lambda$')
plt.grid(True)

plt.savefig("chart_b.png")

