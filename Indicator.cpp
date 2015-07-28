#include "Indicator.h"
#include "Arduino.h"
#include "APM_2_5_PINS.h"

Indicator::Indicator()
{
 blinkInterval =1000;
 gapInterval =1000;

 blueBlinks =0;

previousBlueMillis = millis();
 blueCount= 0;

 blueLedState =0;
 pinMode(BLUE_LED, OUTPUT); 
}

void Indicator::run()
{
unsigned long currentMillis = millis();
  
   if(currentMillis - previousBlueMillis > blinkInterval) {
    // save the last time you blinked the LED 
    previousBlueMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (blueLedState == 0)
      blueLedState = 1;
    else
      blueLedState = 0;

    // set the LED with the ledState of the variable:
    digitalWrite(BLUE_LED, blueLedState);
  }
}

