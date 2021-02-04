#include "NcaPMSensorLight.h"

NcaPMSensorLight::NcaPMSensorLight(Stream& serialPort) {
  _serialPort = (Stream*)&serialPort;
  _currentPos = 0;
}
 
/*
   Checks and process data from serial port
   Returns true if new data is available
*/
bool NcaPMSensorLight::Process() {
  byte currentChar;
  bool result = false;
  while (_serialPort->available() > 0) {
    currentChar = _serialPort->read();
    if (currentChar == HEAD1 && _previousChar == HEAD0) {
      _currentPos = 1;
      _checkSum = _previousChar + currentChar;
    }
    else {
      if (_currentPos == PM01POS) {
        PM25Value = currentChar * 256;
      }
      else if (_currentPos == PM01POS + 1) {
        PM25Value += currentChar;
		if (PM25Value > 0) {
			HasPM1Data = true;
		}
      }
      if (_currentPos == PM01POS) {
        PM01Value = currentChar * 256;
      }
      else if (_currentPos == PM25POS + 1) {
        PM25Value += currentChar;
      }
      else if (_currentPos == PM10POS) {
        PM10Value = currentChar * 256;
      }
      else if (_currentPos == PM10POS + 1) {
        PM10Value += currentChar;
      }
      else if (_currentPos == PM_DATA_LENGTH - 1) {
        // final char of the data = checksum, we check it and if it's valid we set the new data to true
        if (currentChar + _previousChar * 256 == _checkSum) {
          result = true;
        }
      }
      // we should not include first char of checksum value in the checksum calculation !
      if (_currentPos < PM_DATA_LENGTH - 2) {
        _checkSum += currentChar;
      }
    }
    _previousChar = currentChar;
    _currentPos++;
  }
  return result;
}

