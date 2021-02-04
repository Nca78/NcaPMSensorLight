#include <NcaPMSensorLight.h>

// Demo made for atmega so we need software serial
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, -1);  // only RX is used

NcaPMSensorLight pmSensor(mySerial);

void setup() {
  // put your setup code here, to run once:
  // Start serial port for communicating with sensor
  mySerial.begin(9600);

  // Start serial to report data
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (pmSensor.Process()) {
    // We can read data
    Serial.print(F("PM 2.5: "));
    Serial.println(pmSensor.PM25Value);

    Serial.print(F("PM 10: "));
    Serial.println(pmSensor.PM10Value);

    Serial.print(F("PM 1.0: "));
    if (pmSensor.HasPM1Data) {
      Serial.println(pmSensor.PM25Value);    
    }
    else {
      Serial.println(F(" not available")); 
    }
  }
  else {
    Serial.print(".");
  }
  // Wait, or do something else in a "normal" script
  delay(500);
}
