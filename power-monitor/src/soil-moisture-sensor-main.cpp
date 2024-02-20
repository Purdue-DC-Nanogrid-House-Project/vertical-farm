// Note: This file will be used to ensure wifi connection is stable for data uploading.

#include "soil-moisture-sensor-main.h"
#include "mqtt_comm.h"
#include "ota_comm.h"
#include "serial_comm.h"
#include "wifi_comm.h"
#include "ntp_comm.h"
#include "config.h"
#include "soil-moisture-sensor.h"
#include <Arduino.h>

bool isWiFiConnected = false;
bool isMDNSConnected = false;
bool isMQTTConnected = false;
int loopCount = 0;
int msecBetweenResponderRestarts = 120000;

//shelf #1
valvePin1 = 27;
#define AOUT_PIN_1 26

//shelf #2
valvePin2 = 32;
#define AOUT_PIN_2 33

//shelf #3
valvePin3 = 34;
#define AOUT_PIN_3 35

void setup() {
  InitializeCommunications();
  InitializeSoilMoistureSensors();
}

void loop() {
  ReestablishCommunications(loopCount);
  ReadSoilMoistureSensorData(isMQTTConnected, AOUT_PIN_1, valvePin1, sensorValue1, voltage1);
  ReadSoilMoistureSensorData(isMQTTConnected, AOUT_PIN_2, valvePin2, sensorValue2, voltage2);
  ReadSoilMoistureSensorData(isMQTTConnected, AOUT_PIN_3, valvePin3, sensorValue3, voltage3);
  SynchronizeDateTime();
  delay(Config::LOOP_INTERVAL_MSEC);
  loopCount += 1;

  // don't check the soil moisture for 1 minute
  delay(60000);
}

void InitializeCommunications() {
    EstablishSerialCommunication();
    isWiFiConnected = EstablishWiFiCommunication();
    if(isWiFiConnected) {
        isMDNSConnected = EstablishMDNSResponder();
        EstablishOTAServer();
        isMQTTConnected = EstablishMQTTConnection();
    }
}

void ReestablishCommunications(int &loopCount) {
    // Reestablish communications if necessary
    if(!isWiFiConnected) { isWiFiConnected = EstablishWiFiCommunication(); }
    if(!isMDNSConnected) { isMDNSConnected = EstablishMDNSResponder(); }
    if(!isMQTTConnected) { isMQTTConnected = EstablishMQTTConnection(); }

    // Restart the MDNS Responder if necessary
    if (loopCount == (msecBetweenResponderRestarts/Config::LOOP_INTERVAL_MSEC)) {
        isMDNSConnected = RestartMDNSResponder();
        loopCount = 0;  // Reset the loop count
    }
}

