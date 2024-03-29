# Calibration Introduction

The capacitive soil moisture sensors are calibrated using a **gravimetric** soil moisture content process.
Simply weigh a soil sample every time water is added and record the voltage value that is output by the capacitive sensor.
A linear fit to the data can then be applied and a calibration curve can then be coded into the soil moisture sensor's Arduino code.

## Procedure

1. Gather a *dry* soil sample into a 200 ml beaker. Tightly pack the soil down and weigh it. This serves as the 
   dry mass weight m_d. This also is used to calculate the bulk density of the soil rho_ds = m_d/(200 ml)
2. Place the soil sensor into the sample and record the value
3. Add about 10 ml of water (any small amount is fine) and thoroughly mix the sample
4. Weigh the sample with water added
5. Record the voltage after placing the sensor into the soil sample
6. Repeat steps 3-5 until the soil sample is fully saturated with water and record the voltage at that point
7. Compile the sensor measurements into a .csv file with the headers as follows:
   Mass [g] | Voltage [V]
8. Run the soil calibration code after inputting constant values such as the mass of the container, the sensor reading in air,
   and the volume of soil used
9. Change the slope and y-intercept values on the sensor's arduino code accordingly

## Notes

- To create the dry soil sample, there are several options
  1. lay out the soil on wax paper and spread it out as thin as possible and let air dry (4-7 days)
  2. lay sample thinly onto parchment paper and put into 300 <sup>o</sup>F oven for approximately 20 minutes
- A digital food scale is preferred for mass measurements. The more precise your scale is, the better your calibration will be
- The amount of water added in each time doesn't matter, just add a little bit at a time in order to get around 6-10 data samples
- The python script is meant to provide a framework for processing the data, Jupyter notebooks are recommended for use
- The starting sample does not have to be fully dry, simply ensure that it is at least relatively dry to start with for calibration
