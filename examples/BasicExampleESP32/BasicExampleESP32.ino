#include <NcaPMSensorLight.h>

NcaPMSensorLight pmSensor(Serial2);

void setup() {
  // put your setup code here, to run once:
  // Start serial to report data
  Serial.begin(115200);
  
  // Start serial port for communicating with sensor
  Serial2.begin(9600);  // Only RX is used, on pin 16 (default for Serial2)
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
