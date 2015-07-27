#include "ComsDecoder.h"
#include "Arduino.h"

ComsDecoder::ComsDecoder()
{
}

void ComsDecoder::processMessage(uint8_t *data, uint8_t dataLength)
{
	Serial.println("New Message");
	for (int i = 0; i < dataLength; i++)
	{
		Serial.print((char)data[i]);
	}
}

void ComsDecoder::sendFailure()
{

}

void ComsDecoder::receiveFailure()
{

}