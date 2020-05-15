import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results.txt" #file = "results3.txt"
data = np.loadtxt(file)
file2 = "results2.txt"
data2 = np.loadtxt(file2)

x=data[:,0]
Wn=data[:,1]
y=data[:,2]
x2=data2[:,0]
dots=data2[:,1]

plt.subplot(2,2,1)
plt.plot(x[0:1000], Wn[0:1000], color='#188bff')

plt.plot(x[0:1000], y[0:1000], linewidth=0.5, color='black')

plt.legend(['n=5', 'f(x)'], loc=8) #loc=2)
plt.plot(x2[0:6], dots[0:6], linestyle='', color='#00008b', marker='.')

plt.xlabel('x')
plt.grid(True)

plt.subplot(2,2,2)
plt.plot(x[1001:2002], Wn[1001:2002], color='#188bff')

plt.plot(x[1001:2002], y[1001:2002], linewidth=0.5, color='black')

plt.legend(['n=10', 'f(x)'], loc=9) #loc=2)
plt.plot(x2[6:17], dots[6:17], linestyle='', color='#00008b', marker='.')

plt.xlabel('x')
plt.grid(True)

plt.subplot(2,2,3)
plt.plot(x[2002:3003], Wn[2002:3003], color='#188bff')

plt.plot(x[2002:3003], y[2002:3003], linewidth=0.5, color='black')

plt.legend(['n=15', 'f(x)'], loc=9) #loc=2)
plt.plot(x2[17:33], dots[17:33], linestyle='', color='#00008b', marker='.')

plt.xlabel('x')
plt.grid(True)

plt.subplot(2,2,4)
plt.plot(x[3003:4004], Wn[3003:4004], color='#188bff')

plt.plot(x[3003:4004], y[3003:4004], linewidth=0.5, color='black')

plt.legend(['n=20', 'f(x)'], loc=8) #loc=2)
plt.plot(x2[33:53], dots[33:53], linestyle='', color='#00008b', marker='.')

plt.xlabel('x')
plt.grid(True)

plt.suptitle('węzły równoodległe') #plt.suptitle('węzły zoptymalizowane')
plt.subplots_adjust(left=0.08, bottom=0.1, right=0.98, top=0.93, wspace=0.2, hspace=0.4)
#plt.show()

plt.savefig("chart1.png") #plt.savefig("chart2.png")
