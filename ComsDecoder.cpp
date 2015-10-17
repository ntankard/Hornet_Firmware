#include "ComsDecoder.h"
#include "Arduino.h"
#include "CONFIG.h"
#include "HornetManager.h"


ComsDecoder::ComsDecoder()
{
	test = 0;
}

volatile MessageBuffer_Passer* ComsDecoder::processMessage(uint8_t *data, uint8_t dataLength)
{
	volatile MessageBuffer_Passer* toSend;
	/*TP("EOPs");

	for (int i = 0; i < dataLength; i++)
	{
		Serial.write(data[i]);
	}
	Serial.write('\n');

	TP("EOPe");*/

	switch (data[2])
	{
	case C_COMS_CODE_CONNECT_CONFIRM:
		_charMessage.setID(data[0]);
		return &_charMessage;
	case MB_ARM_DISARM:
		test++;
		TP("RAW COM" + (String)test);
		if (dataLength != 2)
		{
			break;//@TODO throw
		}
		toSend = _ArmDisarmSender.getAvailable();
		for (int i = 0; i < dataLength; i++)
		{
			toSend->getPacket()[i] = data[i + 2];
		}
		return toSend;
	case MB_JOY_XY:
		if (dataLength != 5)
		{
			break;//@TODO throw
		}
		toSend = _XYJoySender.getAvailable();
		for (int i = 0; i < dataLength; i++)
		{
			toSend->getPacket()[i] = data[i+2];
		}
		return toSend;
	case MB_JOY_THROTTLE:
		if (dataLength != 3)
		{
			break;//@TODO throw
		}
		toSend = _throttleJoySender.getAvailable();
		for (int i = 0; i < dataLength; i++)
		{
			toSend->getPacket()[i] = data[i + 2];
		}
		return toSend;
	case MB_JOY_Z:
		if (dataLength != 3)
		{
			break;//@TODO throw
		}
		toSend = _ZJoySender.getAvailable();
		for (int i = 0; i < dataLength; i++)
		{
			toSend->getPacket()[i] = data[i + 2];
		}
		return toSend;
	default:
		//@TODO message error
		break;
	}

	// unknown message, forward it on (ADD ERROR HERE)
	_charMessage.setID(data[0]);
	return &_charMessage;
}

int16_t toInt16_t(uint8_t *data)
{
	return (data[1] << 8) || data[0];
}

void ComsDecoder::sendFailure()
{
	//@TODO this
}

void ComsDecoder::receiveFailure()
{
	//@TODO this
}
