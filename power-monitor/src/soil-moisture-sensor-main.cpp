// Note: This file will be used to ensure wifi connection is stable for data uploading.

#include "main.h"
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

void setup() {
  InitializeCommunications();
  InitializeSoilMoistureSensors();
}

void loop() {
  ReestablishCommunications(loopCount);
  ReadSoilMoistureSensorData(isMQTTConnected, AOUT_PIN_1, valvePin1, sensor_value_1, voltage_1);
  SynchronizeDateTime();
  delay(Config::LOOP_INTERVAL_MSEC);
  loopCount += 1;
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

