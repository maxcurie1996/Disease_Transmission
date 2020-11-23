import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

#i_list=[2,10,20,30,40,50,200]

for i in range(1,11):
#for i in i_list:
	Title="Vaccination rate"
	#Title="Neighbor"
	path="Lower/V_scan/"
	if i<10:
		suffix="_0"+str(i)
	else:
		suffix="_"+str(i)
	data=pd.read_csv(path+'COVID'+suffix+'.csv')  

	plt.clf()

	plt.plot(data['days'],data['Susceptible'],label='Susceptible')
	plt.plot(data['days'],data['Infected'],label='Infected')
	plt.plot(data['days'],data['Recovered'],label='Recovered')
	plt.plot(data['days'],data['Vaccinated'],label='Vaccinated')

	plt.xlim(0,100)
	plt.ylim(0,40000)

	plt.legend()
	plt.xlabel('Days',fontsize=10)
	plt.ylabel('Population',fontsize=10)

	#plt.title(Title+"  "+str(i*10)+"%",fontsize=20)
	#plt.show()
	#plt.savefig(path+Title+"  "+str(i*10)+"%"+'.png')

	plt.title(Title+"  "+str(i*10)+"%",fontsize=20)
	#plt.show()
	plt.savefig(path+Title+"  "+str(i)+'.png')

'''
# Create some mock data
t = np.arange(0.01, 10.0, 0.01)
data1 = np.exp(t)
data2 = np.sin(2 * np.pi * t)

fig, ax1 = plt.subplots()

color = 'tab:red'
ax1.set_xlabel('time (s)')
ax1.set_ylabel('exp', color=color)
ax1.plot(t, data1, color=color)
ax1.tick_params(axis='y', labelcolor=color)

ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis

color = 'tab:blue'
ax2.set_ylabel('sin', color=color)  # we already handled the x-label with ax1
ax2.plot(t, data2, color=color)
ax2.tick_params(axis='y', labelcolor=color)

fig.tight_layout()  # otherwise the right y-label is slightly clipped
plt.show()
'''