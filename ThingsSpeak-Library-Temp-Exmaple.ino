#include <Grove_Temperature_And_Humidity_Sensor.h>

DHT dht(D2);

#include "ThingSpeak.h"

unsigned long myChannelNumber = XXXX;    // change this to your channel number
const char * myWriteAPIKey = "XXXX"; // change this to your channels write API key

float temp, humidity;

void setup() {
  ThingSpeak.begin(client);

  Serial.begin(9600);
  dht.begin();

}

void loop() {

temp = String(random(60, 80));
// LETS JUST HAVE A RANDOM TEMP FOR NOW.
//temp = dht.getTempFarenheit();

Serial.printlnf("Temp: ", temp);
//Serial.printlnf("Humidity: %f", humidity);

// Write to ThingSpeak, field 1, immediately
ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey);
delay(20000); // ThingSpeak will only accept updates every 15 seconds.

}