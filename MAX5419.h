/*
* FILENAME:	MAX5419.h
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


#ifndef _MAX5419_H_
#define _MAX5419_H_


#include "Arduino.h"
#include <Wire.h>

// I2C Address of device
#define MAX5419_DEFAULT_ADDRESS	0x28	// A0 is connected to GND
#define MAX5419_ADDRESS_A0_VCC	0x29	// A0 is connected to VCC
#define MAX5419_ADDRESS_A0_GND	0x28	// A0 is connected to GND


// Command definitions (sent to WIPER register)
#define MAX5419_CMD_WRITE	0x00
#define MAX5419_CMD_INC		0x04
#define MAX5419_CMD_DEC		0x08
#define MAX5419_CMD_READ	0x0C

// Register addresses
#define MAX5419_RA_WIPER	0x00


// Common WIPER values
#define MAX5419_WIPER_MID	0x080
#define MAX5419_WIPER_A		0x100
#define MAX5419_WIPER_B		0x000

class MAX5419 {
    public:
        MAX5419();
        MAX5419(uint8_t address);
        
        void begin(void);
        bool testConnection(void);

	// Write the Wiper register
	bool setWiper(uint16_t value);  // returns true if no errors
        
	// Increments the Wiper register
	bool incWiper(void);  // increments the wiper register - stops at 0x100

	// Decrements the Wiper register
	bool decWiper(void);  // decrements the wiper register - stops at 0x000

     // Read the Wiper register
     int16_t getWiper(void);  // returns -1 if errors

    private:
        uint8_t devAddr;
        uint16_t buffer;
};

#endif /* _MAX5419_H_ */