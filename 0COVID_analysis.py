import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

#i_list=[2,10,20,30,40,50,200]
x=[]
data0=[]
data1=[]
for i in range(1,11):
#for i in i_list:
	#Title="Vaccination rate"
	Title="Infection rate"
	#Title="Neighbor"
	path="Data/I_scan/"
	if i<10:
		suffix="_0"+str(i)
	else:
		suffix="_"+str(i)
	data=pd.read_csv(path+'COVID'+suffix+'.csv')  

	x.append(i*1)
	data0.append(np.max(data['Infected']))
	data1.append(np.argmax(data['Infected']))

'''
plt.clf()

plt.plot(x,data0)
	
#plt.legend()
plt.xlabel(Title+"",fontsize=10)
plt.ylabel('Peak Infection Count',fontsize=10)

plt.title(Title+" Scan",fontsize=20)
#plt.show()
plt.savefig(path+Title+"_a"+'.png')

'''

plt.clf()

plt.plot(x,data1)
	
#plt.legend()
plt.xlabel(Title+"(%)",fontsize=10)
plt.ylabel('Time to reach peak(days)',fontsize=10)

plt.title(Title+" Scan",fontsize=20)
#plt.show()
plt.savefig(path+Title+"_t"+'.png')

