/*
* FILENAME:	MAX5419.cpp
* AUTHOR:	Rohit Srivastava
* EMAIL:	srivas29@purdue.edu
* VERSION:	0.0

* DISCLAIMER
* This code is in the public domain. Please feel free to use, modify, distribute,
* etc. as needed, but please give reference to original author as a courtesy to
* open source developing/-ers.
*
* If you find any bugs in the code, or have any questions, please feel free to
* contact me.


*/


#include "MAX5419.h"

/** Default constructor, uses default I2C address.
 * @see MAX5419_DEFAULT_ADDRESS
 */
MAX5419::MAX5419() {
    devAddr = MAX5419_DEFAULT_ADDRESS;
}

/** Specific address constructor.
 * @param address I2C address
 * @see MAX5419_DEFAULT_ADDRESS
 * @see MAX5419_ADDRESS_A0_GND
 * @see MAX5419_ADDRESS_A0_VCC
 */
MAX5419::MAX5419(uint8_t address) {
    devAddr = address;
}

void MAX5419::begin() {
  setWiper(MAX5419_WIPER_MID);	// set to mid scale
}

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return True if connection is valid, false otherwise
 */
bool MAX5419::testConnection() {
    Wire.beginTransmission(devAddr);
    return (Wire.endTransmission() == 0);
}

/** Set Wiper value
 * valid range is 0x000 = B to 0x100 = A
 * setting wiper in the range 0x101 to 0x3FF will lock wiper at A w/ inc & dec disabled
 */
bool MAX5419::setWiper(uint16_t value) {
  Wire.beginTransmission(devAddr);
  uint8_t temp = ((value >> 8 & 0x01) | MAX5419_CMD_WRITE);
  Wire.write(temp);
  temp = (value & 0xFF);
  Wire.write(temp);
  return (Wire.endTransmission() == 0);
}
 
/** Increment Wiper value (one step closer to A)
 * will not increment past 0x100
 */
bool MAX5419::incWiper() {
  Wire.beginTransmission(devAddr);
  Wire.write(MAX5419_CMD_INC);
  return (Wire.endTransmission() == 0);
}
 
/** Decrement Wiper value (one step closer to B)
 * will not decrement past 0x000
 */
bool MAX5419::decWiper() {
  Wire.beginTransmission(devAddr);
  Wire.write(MAX5419_CMD_DEC);
  return (Wire.endTransmission() == 0);
}
 
/** Read Wiper value
 */
int16_t MAX5419::getWiper() {
  Wire.beginTransmission(devAddr);
  Wire.write(MAX5419_CMD_READ);
  if(Wire.endTransmission() == 0) {
    if(Wire.requestFrom(devAddr, (uint8_t) 2) == 2) {
      buffer = Wire.read();
      buffer <<= 8;
      buffer |= Wire.read();
      return buffer;
    }
    else return -1;
  }
  else return -1;
}