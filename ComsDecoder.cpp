#include "ComsDecoder.h"
#include "Arduino.h"
#include "CONFIG.h"

ComsDecoder::ComsDecoder(HornetManager* theManager)
{
	_theManager = theManager;
}

void ComsDecoder::processMessage(uint8_t *data, uint8_t dataLength)
{
	switch (data[0])
	{
	case C_COMS_CODE_CONNECT_CONFIRM:
		_theManager->M_ConnectionConfirmed();
		break;
	case C_COMS_CODE_RESET:
		_theManager->M_Reset();
		break;
	case C_COMS_CODE_THROTTLE:
		_theManager->ND_Throttle((int)data[1]);
		break;
	default:
		//@TODO message error
		break;
	}
}

void ComsDecoder::sendFailure()
{

}

void ComsDecoder::receiveFailure()
{

}
