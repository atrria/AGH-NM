import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results3.txt"
data = np.loadtxt(file)

y=data

plt.plot(y, color="red", linewidth=1)

#plt.show()
plt.savefig("chart3.png")