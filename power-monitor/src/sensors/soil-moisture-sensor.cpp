void setup() {
	Serial.begin(115200);
	pinMode (valvePin, OUTPUT);
}

void ReadSoilMoistureSensorData(bool isMQTTConnected, int AOUT_PIN, int valvePin, float sensorValue, int voltage, int shelfNumber){

	sensorValue = analogRead(AOUT_PIN);
	convertedSensorVoltage = sensorValue/4095*3.3; //this math hasn't worked for me previously, so you may need to go back to the strategy i used in the Arduino IDE

if((convertedSensorVoltage) > voltage){
	// soil is dry and needs to be watered! turn valve ON
	digitalWrite(valvePin, HIGH);

	// leave valve on for 15 seconds
	delay(45000);

	// turn valve OFF
	digitalWrite(valvePin, LOW);

  } else {
	// soil is moist, keep valve closed and do not water
	digitalWrite(valvePin, LOW);

	// don't check the soil moisture for 10 hours
	delay(36000000);
  }
delay(1000);

    // Print out the measured values from each soil moisture sensor

        String dataName = "SoilMoistureSensorShelf " + shelfNumber + " Voltage";
        String payloadData = String(convertedSensorVoltage);
        String payloadUnits = "(V)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

    
}