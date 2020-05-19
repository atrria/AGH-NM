import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results_first_half.txt" # "results_second_half.txt"
data = np.loadtxt(file)
m=1
n=200
for i in np.arange(0,6):
	alfa = data[(m+n*i):(n+2+m+n*i), 0]
	values = data[(m+n*i):(n+2+m+n*i), 1]
	plt.plot(alfa, values)
	m=m+3

plt.grid(True)
plt.rc('text', usetex=True)
plt.legend([r'$u_0(x)$', r'$u_1(x)$', r'$u_2(x)$', r'$u_3(x)$', r'$u_4(x)$', r'$u_5(x)$'], loc=2)
plt.rc('text', usetex=False)
plt.title('Wykres 3') # ('Wykres 4')
plt.xlabel('x')
plt.ylabel('u(x)')

plt.savefig("chart3.png") # ("chart4.png")

