
#include "XBee.h"


#include <inttypes.h>
#include "Rx16Response.h"
#include "Rx64Response.h"
#include "Tx16Request.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

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




// allocate two bytes for to hold a 10-bit analog reading
uint8_t payload[] = { 1, 2 };

// with Series 1 you can use either 16-bit or 64-bit addressing

// 16-bit addressing: Enter address of remote XBee, typically the coordinator
Tx16Request tx = Tx16Request(0x0000, payload, sizeof(payload));






void setup() {

	// data out
	Serial.begin(9600);
	Serial.println("Begin");

	// toXBee
	Serial3.begin(9600);
	xbee.setSerial(Serial3);
}

// continuously reads packets, looking for RX16 or RX64
void loop() {

	// print raw packet
	/*if (Serial3.available())
	{
		Serial.println(toHex(Serial3.read()));
	}*/

	xbee.send(tx);
	delay(1000);
	
	/*xbee.readPacket();
	if (xbee.getResponse().isAvailable()) {
		Serial.println("S");
		Serial.println(xbee.getResponse().getApiId());
		Serial.println("S");
		// got something
		if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
			// got a rx packet
			// Serial.print("YES2 ");
			if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
				Serial.print("YES3 ");
				xbee.getResponse().getRx16Response(rx16);
				option = rx16.getOption();
				data = rx16.getData(0);
				//Serial.print(data);
				Serial.println(rx16.getData(0));
				Serial.println(rx16.getData(1));
				Serial.println(rx16.getData(2));
				Serial.println(rx16.getData(3));
			} else {
				Serial.print("YES4 ");
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

