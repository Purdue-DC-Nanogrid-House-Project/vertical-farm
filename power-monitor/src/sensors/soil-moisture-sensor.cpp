void setup() {
	Serial.begin(115200);
	pinMode (valvePin, OUTPUT);
}

void ReadSoilMoistureSensorData(bool isMQTTConnected, int AOUT_PIN, int valvePin, float sensor_value, int voltage){

	sensor_value = analogRead(AOUT_PIN);

if((sensor_value/4095*3.3) > voltage){

    //soil is dry and needs to be watered!
    digitalWrite(valvePin, HIGH); //turn valve ON
    moistureVoltage = sensor_value/4095*3.3;
    Serial.print(" - Valve open \n"); --> don't need this
    delay(45000); //leave valve on for 15 seconds
    digitalWrite(valvePin, LOW); //turn valve OFF
  } else {
    //soil is moist, do not water
    digitalWrite(valvePin, LOW);
    Serial.print((sensor_value/4095*3.3));
    Serial.print(" - Valve closed \n"); --> don't need this
    //delay(36000000); //don't check the soil moisture for 10 hours
  }
delay(1000);

    // Print out the measured values from each soil moisture sensor

        String dataName = "SoilMoistureSensor " + shelfName + " Voltage";
        String payloadData = String(moistureVoltage);
        String payloadUnits = "(V)";
        LogSensorData(dataName, payloadData, payloadUnits);
        RecordData(dataName, payloadData, payloadUnits, isMQTTConnected);

    }
}