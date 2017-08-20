
#include "MBme280.h"
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000
#define SERIAL_BAUD 115200
MBme280 bmeSenSor;
uint32_t tsLastReport = 0;
PulseOximeter pox;
void setup() {
	Serial.begin(SERIAL_BAUD);
	while (!Serial) {} // Wait
	while (!bmeSenSor.begin()) {
		Serial.println("Could not find BME280 sensor!");
		delay(1000);
	}
	if (!pox.begin()) {
		Serial.println("FAILED");
		for (;;);
	}
	else {
		Serial.println("SUCCESS");
	}

}

void loop() {
	/*printBME280Data(&Serial);
	printBME280CalculatedData(&Serial);*/
	bmeSenSor.printBME280Data(&Serial);
	bmeSenSor.printBME280Data(&Serial);
	pox.update();
	if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
		Serial.print("Heart rate:");
		Serial.print(pox.getHeartRate());
		Serial.print("bpm / SpO2:");
		Serial.print(pox.getSpO2());
		Serial.print("% / temp:");
		Serial.print(pox.getTemperature());
		Serial.println("C");

		tsLastReport = millis();
	}
	delay(500);
}
