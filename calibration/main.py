import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

## Relevant Data 
## --CHANGE THE VALUES FOR THE EXPERIMENT IN WHICH YOU RAN--

#Reading in the data
df = pd.read_csv("SensorCalibrationTrial2'.csv")

m_c = 22.7           #[g]    mass of container
m_d = 29.8           #[g]    dry mass of soil in trial
sensor_in_air = 2.63 #[V]    Voltage
v = 200              #[ml]   volume of soil used
rho_water = 0.997    #[g/ml] density of water
rho_ds = m_d/v       #[g/ml] bulk density trial

#Calculating the theta_v values and inverse voltage
theta_v = ((df['Mass [g]'] - m_c - m_d)/m_d)*(rho_ds/rho_water)
V_inv = 1/df["Voltage"]

#Creates a new column for these values
df.insert(2, 'Theta_v',theta_v,True)
df.insert(3, 'Inverse Voltage',V_inv,True)

#Calculates the slope and intercept of the line of best fit
line = np.polyfit(df["Inverse Voltage"],df["Theta_v"], 1)
poly = np.poly1d(line)
x = np.linspace(np.min(V_inv),np.max(V_inv),100)

#Gives the relevant slope and y-intercept [m b]
m = round(line[0],3)
b = round(line[1],3)

print(m)
print(b)

#Plots the data and the calibration curve
plt.figure()
plt.scatter(df["Inverse Voltage"],df["Theta_v"])
plt.plot(x, poly(x),'r', label='y={}x+({})'.format(m,b))
plt.xlabel('Inverse of Voltage [V^-1]')
plt.ylabel('Theta_v [cm^3/cm^3]')
plt.title('Calculated Moisture Content vs. Inverse Voltage Measured')
plt.legend(loc='best')
