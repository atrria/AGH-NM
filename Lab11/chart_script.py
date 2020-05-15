import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results1.txt"
data = np.loadtxt(file)

x=data[:,0]
y=data

plt.plot(x,y[:,2], color="red")
plt.plot(x,y[:,1], color="black")

#plt.show()
plt.savefig("chart1.png")