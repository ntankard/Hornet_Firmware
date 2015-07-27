/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "XBee.h"
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <inttypes.h>
/*
This example is for Series 1 XBee (802.15.4)
Receives either a RX16 or RX64 packet and sets a PWM value based on packet data.
Error led is flashed if an unexpected packet is received
*/

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();

int statusLed = 11;
int errorLed = 12;
int dataLed = 10;

uint8_t option = 0;
uint8_t data = 0;
String toHex(uint8_t b);
String toHex(uint8_t b)
{
  String hex[] ={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
  uint8_t hi;
  uint8_t lo;
  hi = (b>>4);
  lo = (b & 0b00001111);
  return hex[hi] + hex[lo];
}

void setup() {

  // start serial
  Serial.begin(9600);
  Serial3.begin(9600);
  xbee.setSerial(Serial3);
  
  Serial.println("start");
}

// continuously reads packets, looking for RX16 or RX64
void loop() {
    
   
    if(Serial3.available())
    {
      Serial.println(toHex(Serial3.read()));
    }
    /* xbee.readPacket();
    if (xbee.getResponse().isAvailable()) {
      // got something
    //  Serial.print("YES1 ");
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
        // got a rx packet
       // Serial.print("YES2 ");
        if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
          //Serial.print("YES3 ");
                xbee.getResponse().getRx16Response(rx16);
          option = rx16.getOption();
          data = rx16.getData(0);
          //Serial.print(data);
                    Serial.println(rx64.getData(0));
          Serial.println(rx64.getData(1));
          Serial.println(rx64.getData(2));
          Serial.println(rx64.getData(3));
        } else {
          //Serial.print("YES4 ");
                xbee.getResponse().getRx64Response(rx64);
          option = rx64.getOption();
          data = rx64.getData(0);
          Serial.println(rx64.getData(0));
          Serial.println(rx64.getData(1));
          Serial.println(rx64.getData(2));
          Serial.println(rx64.getData(3));
        }
        
        // TODO check option, rssi bytes    
       // flashLed(statusLed, 1, 10);
        
        // set dataLed PWM to value of the first byte in the data
        //analogWrite(dataLed, data);
      } else {
        // not something we were expecting
       // flashLed(errorLed, 1, 25);    
      }
    } else if (xbee.getResponse().isError()) {
      //nss.print("Error reading packet.  Error code: ");  
      //nss.println(xbee.getResponse().getErrorCode());
      // or flash error led
    } */
}

