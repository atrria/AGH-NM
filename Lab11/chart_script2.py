import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results2.txt"
data = np.loadtxt(file)

y=data

plt.plot(y, color="red", linewidth=1)

#plt.show()
plt.savefig("chart2.png")