// I, Damanpreet Singh, student number 000741359, certify that all code submitted is my own work;
// that I have not copied it from any other source.
// I also certify that I have not allowed my work to be copied by others.

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

DeviceAddress thermometer;

void convertAddress(DeviceAddress deviceAddress)
{
  // Convert the address to a string
  char addressString[17];
  for (uint8_t i = 0; i < 8; i++)
  {
    if (thermometer[i] < 16) sprintf(addressString + (i * 2), "0");
    sprintf(addressString + (i * 2), "%X", thermometer[i]);
  }
  
  Serial.println(addressString);
}


void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);
  DS18B20.begin();

  Serial.println("\n");
  Serial.println("Temperature Application");

  if (!DS18B20.getAddress(thermometer, 0)) {
    Serial.println("NO DS18B20 temperature are installed!");
    while (1);
  }
  else{
    Serial.print("Found DS18B20 sensor with address " );
    DS18B20.getAddress(thermometer, 0);
    convertAddress(thermometer);
  }
}


void loop()
{
  float fTemp;
  String condition;

  // ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();

  // fetch the temperature.  We only have 1 sensor, so the index is 0.
  fTemp = DS18B20.getTempCByIndex(0);
  if (fTemp < 10)
  {
    condition = " Cold!";
  }
  else if (fTemp > 10 && fTemp < 15)
  {
    condition = " Cool";
  }
  else if (fTemp > 15 && fTemp < 25)
  {
    condition = " Perfect ";
  }
  else if (fTemp > 25 && fTemp < 30)
  {
    condition = " Warm";
  }
  else if (fTemp > 30 && fTemp < 35)
  {
    condition = " Hot";
  }
  else if (fTemp > 35)
  {
    condition = " Too Hot!";
  }

  // print the temp to the USB serial monitor
  Serial.println("Current temperature is: " + String(fTemp) + "° C or" + condition);

  delay(5000);
}