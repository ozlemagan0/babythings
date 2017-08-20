// MBme280.h

#ifndef _MBME280_h
#define _MBME280_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "MBme280.h"
	#include <BME280I2C.h>
	#include "Arduino.h"
	
#else
	#include "WProgram.h"
#endif
class MBme280
{
public:
	bool metric = false;
	MBme280();
	bool begin();
	void printBME280Data(Stream * client);
	/* === Print a message to stream with the altitude, and dew point. === */
	void printBME280CalculatedData(Stream* client);
private:
	BME280I2C bme;
};



#endif

