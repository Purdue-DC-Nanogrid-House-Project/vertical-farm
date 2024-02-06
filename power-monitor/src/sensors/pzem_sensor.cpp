#include "config.h"
#include "serial_comm.h"
#include "mqtt_comm.h"
#include "pzem_sensor.h"
#include <PZEM004Tv30.h>

//hello emma?

const int valvePin1 = 27;
#define AOUT_PIN_1 26

float value_1;
const int voltage_1 = 2.3;

void setup() {
	Serial.begin(115200);
	pinMode (valvePin1, OUTPUT);
}

void loop() {
	value_1 = analogRead(AOUT_PIN_1);

if((value_1/4095*3.3) > voltage_1){
    //soil is dry and needs to be watered!
    digitalWrite(valvePin1, HIGH); //turn valve ON
    Serial.print((value_1/4095*3.3));
    Serial.print(" - Valve open \n");
    delay(45000); //leave valve on for 15 seconds
    digitalWrite(valvePin1, LOW); //turn valve OFF
  } else {
    //soil is moist, do not water
    digitalWrite(valvePin1, LOW);
    Serial.print((value_1/4095*3.3));
    Serial.print(" - Valve closed \n");
    //delay(36000000); //don't check the soil moisture for 10 hours
  }
delay(1000);
}

void ReadPzemSensorData(bool isMQTTConnected){
    // Print out the measured values from each PZEM module
    for(int i = 0; i < Config::NUMBER_OF_PZEMS; i++)
    {
        // Print the Address of the PZEM
        LogDebugData("PZEM " + String(i) + " - Address:" + String(pzems[i].getAddress()));

        // Read the data from the sensor
        float voltage = pzems[i].voltage();


        String dataName = "SoilMoistureSensor " + String(i) + " Voltage";
        String payloadData = String(voltage);
        String payloadUnits = "(V)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

    }
}