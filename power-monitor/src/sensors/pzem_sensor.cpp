void setup() {
	Serial.begin(115200);
	pinMode (valvePin, OUTPUT);
}

void loop() {
	sensor_value = analogRead(AOUT_PIN);

if((sensor_value/4095*3.3) > voltage){

    //soil is dry and needs to be watered!
    digitalWrite(valvePin, HIGH); //turn valve ON
    Serial.print((sensor_value/4095*3.3));
    Serial.print(" - Valve open \n");
    delay(45000); //leave valve on for 15 seconds
    digitalWrite(valvePin, LOW); //turn valve OFF
  } else {
    //soil is moist, do not water
    digitalWrite(valvePin, LOW);
    Serial.print((sensor_value/4095*3.3));
    Serial.print(" - Valve closed \n");
    //delay(36000000); //don't check the soil moisture for 10 hours
  }
delay(1000);
}

void ReadPzemSensorData(bool isMQTTConnected){ ----> i haven't messed with this
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