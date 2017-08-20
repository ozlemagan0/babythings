
#include <ESP8266HTTPClient.h>
#include "MBme280.h"
#include "MAX30100_PulseOximeter.h"
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

const char* ssid = "BAYKAL";
const char* password = "34an8124ALB9949";


#define REPORTING_PERIOD_MS     1000
#define REPORTING_PERIOD_MS2     50
#define SERIAL_BAUD 115200
MBme280 bmeSenSor;
uint32_t tsLastReport = 0,tsLastReport2=0;
PulseOximeter pox;
StaticJsonBuffer<1024> jsonBuffer;
ESP8266WiFiMulti WiFiMulti;
void GetJsonData();
String result;
HTTPClient http;
void SendToCloud(String data);
void setup() {
	Serial.begin(SERIAL_BAUD);

	while (!Serial) {} // Wait


	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());


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

	if (millis()- tsLastReport2 > REPORTING_PERIOD_MS2)
	{
		pox.update();
		bmeSenSor.update();
		tsLastReport2 = millis();
	}
	
	if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

		GetJsonData();
		Serial.println(result);
		SendToCloud(result);
		result = "";
		tsLastReport = millis();
	}
	delay(100);
}

void GetJsonData()
{
	DynamicJsonBuffer jsonBuffer(128);
	JsonObject& root = jsonBuffer.createObject();
	root["tmp"] = pox.getTemperature();
	root["spo2"] = pox.getSpO2();
	root["bpm"] = pox.getHeartRate();
	root["pres"] = bmeSenSor.pres;
	root["hum"] = bmeSenSor.hum;
	root["alt"] = bmeSenSor.altitude;
	root.printTo(result);
}

void SendToCloud(String data)
{



	http.begin("http://babythings.azurewebsites.net/api/data"); //HTTP
	http.addHeader("content-type", "application/json");
		// start connection and send HTTP header
	int httpCode = http.POST(data);

	// httpCode will be negative on error
	if (httpCode > 0) {
		// HTTP header has been send and Server response header has been handled
		Serial.printf("[HTTP] POST... code: %d\n", httpCode);

		// file found at server
		if (httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			Serial.println(payload);
		}
	}
	else {
		Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
	}

	http.end();
}
