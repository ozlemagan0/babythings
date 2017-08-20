
#include "MBme280.h"
#define SERIAL_BAUD 115200
MBme280 bmeSenSor;
void setup() {
	Serial.begin(SERIAL_BAUD);
	while (!Serial) {} // Wait
	while (!bmeSenSor.begin()) {
		Serial.println("Could not find BME280 sensor!");
		delay(1000);
	}
}

void loop() {
	/*printBME280Data(&Serial);
	printBME280CalculatedData(&Serial);*/
	bmeSenSor.printBME280Data(&Serial);
	bmeSenSor.printBME280Data(&Serial);
	delay(500);
}
