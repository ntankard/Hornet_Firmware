#include "ComsDecoder.h"
#include "Arduino.h"
#include "CONFIG.h"
#include "HornetManager.h"


ComsDecoder::ComsDecoder()
{
}

volatile MessageBuffer_Passer* ComsDecoder::processMessage(uint8_t *data, uint8_t dataLength)
{

	switch (data[0])
	{
	case C_COMS_CODE_CONNECT_CONFIRM:
		_charMessage.setID(data[0]);
		return &_charMessage;
	default:
		//@TODO message error
		break;
	}

	// unknown message, forward it on (ADD ERROR HERE)
	_charMessage.setID(data[0]);
	return &_charMessage;
}

void ComsDecoder::sendFailure()
{
	//@TODO this
}

void ComsDecoder::receiveFailure()
{
	//@TODO this
}
