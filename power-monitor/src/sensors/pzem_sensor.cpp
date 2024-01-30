#include "config.h"
#include "serial_comm.h"
#include "mqtt_comm.h"
#include "pzem_sensor.h"
#include <PZEM004Tv30.h>

void ReadPzemSensorData(bool isMQTTConnected){
    // Print out the measured values from each PZEM module
    for(int i = 0; i < Config::NUMBER_OF_PZEMS; i++)
    {
        // Print the Address of the PZEM
        LogDebugData("PZEM " + String(i) + " - Address:" + String(pzems[i].getAddress()));

        // Read the data from the sensor
        float voltage = pzems[i].voltage();


        String dataName = "PZEM " + String(i) + " Voltage";
        String payloadData = String(voltage);
        String payloadUnits = "(V)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

    }
}