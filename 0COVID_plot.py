import numpy as np
import matplotlib.pyplot as plt
import pandas as pd




path="Lower/N_scan/"
data=pd.read_csv(path+'COVID_02.csv')  

plt.clf()
plt.plot(data['days'],data['Susceptible'],label='Susceptible')
plt.plot(data['days'],data['Infected'],label='Infected')
plt.plot(data['days'],data['Recovered'],label='Recovered')
plt.plot(data['days'],data['Vaccinated'],label='Vaccinated')

plt.ylim(0,40000)

plt.legend()
plt.xlabel('Days',fontsize=10)
plt.ylabel('Population',fontsize=10)

plt.title("Baseline",fontsize=20)
#plt.show()
plt.savefig(path+"Baseline"+'.png')

