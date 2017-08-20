// 
// 
// 

#include "MBme280.h"




MBme280::MBme280()
{
}


bool MBme280::begin()
{
	return bme.begin();
}

void MBme280::printBME280Data(Stream * client)
{
	float temp(NAN), hum(NAN), pres(NAN);
	uint8_t pressureUnit(3);                                           // unit: B000 = Pa, B001 = hPa, B010 = Hg, B011 = atm, B100 = bar, B101 = torr, B110 = N/m^2, B111 = psi
	bme.read(pres, temp, hum, metric, pressureUnit);                   // Parameters: (float& pressure, float& temp, float& humidity, bool celsius = false, uint8_t pressureUnit = 0x0)
																	   /* Alternatives to ReadData():
																	   float temp(bool celsius = false);
																	   float pres(uint8_t unit = 0);
																	   float hum();

																	   Keep in mind the temperature is used for humidity and
																	   pressure calculations. So it is more effcient to read
																	   temperature, humidity and pressure all together.
																	   */
	client->print("Temp: ");
	client->print(temp);
	client->print("°" + String(metric ? 'C' : 'F'));
	client->print("\t\tHumidity: ");
	client->print(hum);
	client->print("% RH");
	client->print("\t\tPressure: ");
	client->print(pres);
	client->print(" atm");
}

void MBme280::printBME280CalculatedData(Stream * client)
{
	float altitude = bme.alt(metric);
	float dewPoint = bme.dew(metric);
	client->print("\t\tAltitude: ");
	client->print(altitude);
	client->print((metric ? "m" : "ft"));
	client->print("\t\tDew point: ");
	client->print(dewPoint);
	client->println("°" + String(metric ? 'C' : 'F'));

}
