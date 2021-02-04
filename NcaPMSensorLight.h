/*
   Arduino Library for Honeywell HPMA1150 and Plantower PM sensors
*/
#ifndef DUSTSENSOR_H
#define DUSTSENSOR_H

#include <Arduino.h>

// Length of PM data in bytes
#define PM_DATA_LENGTH 32

#define HEAD0 0x42
#define HEAD1 0x4d

/* 
Note from Plantower datasheet 

The standard particle mass concentration value refers to the mass concentration value obtained by density conversion using industrial metal particles as equivalent particles, which is suitable for environments such as industrial production workshops. 

The mass concentration of particulate matter in the atmospheric environment is calculated by using the main pollutants in the air as equivalent particles for density conversion, which is suitable for ordinary indoor and outdoor atmospheric environments
*/

// Position of data for "standard particulate matter"
//  only this data section is returned for sensors with no PM1 data (HPMA1150, PMS3001, PMS5001, ...)
#define PM01POS 4
#define PM25POS 6
#define PM10POS 8

// Position of data for "atmospheric environment"
// /!\ this data is only available for sensors with PM1 data: PMS7001, PMSA003 and other newer plantower sensors
//#define PM01POS 10
//#define PM25POS 12
//#define PM10POS 14


class NcaPMSensorLight {
  private:
    // Serial port from which to read the data
    Stream* _serialPort;
    // Checksum value
    long _checkSum;
    // Current byte position
    byte _currentPos;
    // Previous byte value
    byte _previousChar;
  public:
	int PM25Value;
    int PM10Value;
	// Set to true if PM1 data (and PM5 by extension...) is detected. 
	bool HasPM1Data;
	// If HasPM1Data is false, this value will always be 0
	int PM01Value;
	
    // Hardware serial constructor
    NcaPMSensorLight(Stream& serialPort);
    /*
       Checks and process data from serial port
       Returns true if new data is available
    */
    bool Process();
};
 
#endif


