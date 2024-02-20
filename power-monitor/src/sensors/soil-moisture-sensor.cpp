void setup() {
	Serial.begin(115200);
	pinMode (valvePin, OUTPUT);
}

void ReadSoilMoistureSensorData(bool isMQTTConnected, int AOUT_PIN, int valvePin, float sensorValue, int voltage, int shelfNumber){

	sensorValue = analogRead(AOUT_PIN);
	convertedSensorVoltage = sensorValue/4095*3.3; //this math hasn't worked for me previously, so you may need to go back to the strategy i used in the Arduino IDE

if(convertedSensorVoltage > voltage){
	// soil is dry and needs to be watered! turn valve ON
	digitalWrite(valvePin, HIGH);

	// leave valve on for 45 seconds
	delay(45000);

	// turn valve OFF
	digitalWrite(valvePin, LOW);

    // Print out the measured values from each soil moisture sensor
        String dataName = "SoilMoistureSensorShelf " + shelfNumber + " Voltage";
        String payloadData = String(convertedSensorVoltage);
        String payloadUnits = "(V)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

  } else {
	// soil is moist, keep valve closed and do not water
	digitalWrite(valvePin, LOW);

    // Print out the measured values from each soil moisture sensor
        String dataName = "SoilMoistureSensorShelf " + shelfNumber + " Voltage";
        String payloadData = String(convertedSensorVoltage);
        String payloadUnits = "(V)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);


  }

delay(1000);
    
}