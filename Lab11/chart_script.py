import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file1 = "results1_10.txt"
file2 = "results2_10.txt"
file3 = "results3_10.txt"
file4 = "results3_8.txt"
file5 = "results3_6.txt"

data1 = np.loadtxt(file1)
data2 = np.loadtxt(file2)
data3 = np.loadtxt(file3)
data4 = np.loadtxt(file4)
data5 = np.loadtxt(file5)

x=data1[:,0]
y=data1[:,1]

plt.plot(x, y, color='#104176', linewidth=1)
plt.title("k=10, sygnał zaszumiony")
plt.xlabel("i")
plt.savefig("chart1_10.png")

plt.clf()

x=data2[:,0]
y=data2[:,2]

plt.plot(x, y, color='#104176', linewidth=1)
plt.title("k=10, transformata Fouriera")
plt.xlabel("$\omega$")
plt.savefig("chart2_10.png")

plt.axis([0,100,-100,600])
plt.savefig("chart2b_10.png")

plt.clf()

x=data3[:,0]
y=data3

plt.plot(x,y[:,1], color='#ff3333')
plt.plot(x,y[:,2], color='#104176', linewidth=1)
plt.title("k=10")
plt.xlabel("i")
plt.legend(["sygnał niezaszumiony","sygnał odszumiony"])
plt.savefig("chart3_10.png")

plt.clf()

x=data4[:,0]
y=data4

plt.plot(x,y[:,2], color='#104176', linewidth=1)
plt.plot(x,y[:,1], color='#ff3333')
plt.title("k=8")
plt.xlabel("i")
plt.legend(["sygnał odszumiony","sygnał niezaszumiony"])
plt.savefig("chart3_8.png")

plt.clf()

x=data5[:,0]
y=data5

plt.plot(x,y[:,2], color='#104176', linewidth=1)
plt.plot(x,y[:,1], color='#ff3333')
plt.title("k=6")
plt.xlabel("i")
plt.legend(["sygnał odszumiony","sygnał niezaszumiony"])
plt.savefig("chart3_6.png")



