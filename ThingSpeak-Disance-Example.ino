include <Grove-Ultrasonic-Ranger.h>

#include "ThingSpeak.h"

Ultrasonic ultrasonic(4);

unsigned long myChannelNumber = XXXX;    // change this to your channel number
const char * myWriteAPIKey = "XXXX"; // change this to your channels write API key

void setup() {
 Serial.begin(9600);
}

void loop() {

 long RangeInCentimeters;

 Serial.println("The distance to obstacles in front is: ");
 
 RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
 Serial.print(RangeInCentimeters);//0~400cm
 Serial.println(" cm");
 
 ThingSpeak.writeField(myChannelNumber, 1, RangeInCentimeters, myWriteAPIKey);
 delay(20000); // ThingSpeak will only accept updates every 15 seconds.

}