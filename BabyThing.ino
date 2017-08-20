
#include "MBme280.h"
#include "MAX30100_PulseOximeter.h"
#include <ArduinoJson.h>
#define REPORTING_PERIOD_MS     1000
#define SERIAL_BAUD 115200
MBme280 bmeSenSor;
uint32_t tsLastReport = 0;
PulseOximeter pox;
StaticJsonBuffer<1024> jsonBuffer;

String& GetJsonData();
String result;

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
	
	pox.update();
	bmeSenSor.update();
	if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
		
		auto jsonData = GetJsonData();
		Serial.println(jsonData);
		tsLastReport = millis();
	}

}

String& GetJsonData()
{	
	DynamicJsonBuffer jsonBuffer(256);
	JsonObject& root = jsonBuffer.createObject();
	root["tmp"] = pox.getTemperature();
	root["spo2"] = pox.getSpO2();
	root["bpm"] = pox.getHeartRate();
	root["pres"] = bmeSenSor.pres;
	root["hum"] = bmeSenSor.hum;
	root["alt"] = bmeSenSor.altitude;
	root.printTo(result);
	return result;
}
