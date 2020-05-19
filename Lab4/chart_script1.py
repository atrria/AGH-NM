import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results.txt"
data = np.loadtxt(file)

alfa = data[:, 0]
values = data[:, 1:]
colors = ['blue', 'green', 'red', 'black', 'purple', 'orange']

for i in np.arange(0,6):
        plt.plot(alfa, values[:, i], colors[i], linewidth=0.6, marker='.', markersize=3)

plt.axis([0,100,-0.05,2])
plt.rc('text', usetex=True)
plt.legend([r'$\omega_0=\sqrt{\lambda_0}$', r'$\omega_1=\sqrt{\lambda_1}$', r'$\omega_2=\sqrt{\lambda_2}$', r'$\omega_3=\sqrt{\lambda_3}$', r'$\omega_4=\sqrt{\lambda_4}$', r'$\omega_5=\sqrt{\lambda_5}$'], loc=1) # legenda
plt.xlabel(r'$\alpha$')
plt.ylabel(r'$\sqrt{\lambda}$')
plt.rc('text', usetex=False)
plt.grid(True)

ax=plt.subplot()
ax.set_yticks([0.00,0.25,0.50,0.75,1.00,1.25,1.50,1.75])
ax.set_yticklabels(['0.00','0.25'])

plt.title('Wykres 2')

plt.savefig("chart2.png")

