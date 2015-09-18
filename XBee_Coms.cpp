#include "XBee_Coms.h"

#ifdef USER_XBEE_COMS

Coms::Coms()
{

	_tx16.setAddress16(C_COMMS_BSTATION_ADDRESS);
	//_tx16 = Tx16Request(C_COMMS_BSTATION_ADDRESS, (uint8_t*)data, 1);

	// setup the conection to the XBEE
	_xbee.begin(C_COMS_PORT);
	_outstandingSent = false;

}

bool Coms::start()
{

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Coms::run()
{
	_xbee.readPacket();
	if (_xbee.getResponse().isAvailable())
	{
		if (_xbee.getResponse().getApiId() == RX_16_RESPONSE)
		{
			// new message
			_xbee.getResponse().getRx16Response(_rx16);
			_pendingMessage = _comsDecoder.processMessage(_rx16.getData(), _rx16.getDataLength());
			return 1;
		}
		else if (_xbee.getResponse().getApiId() == TX_STATUS_RESPONSE)
		{
			_xbee.getResponse().getTxStatusResponse(_txStatus);
			if (_txStatus.getStatus() == SUCCESS)
			{
				// last sent packet was sucsesful
				_outstandingSent = false;
			}
			else
			{
				// packet send failure, retry
				_xbee.send(_tx16);
				_resendCount++;
				if (_resendCount >= C_COMMS_MAX_RETRY)
				{
					_comsDecoder.sendFailure();	//@TODO make this do sompthing useful
					_outstandingSent = false;
				}
			}
		}
		else
		{
			_comsDecoder.receiveFailure();	//@TODO sompthing useful
		}
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Coms::canSend()
{

	return !_outstandingSent;

}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Coms::send(uint8_t *data, uint8_t dataLength)
{
	if (!_outstandingSent)
	{
		_resendCount = 0;
		_outstandingSent = true;

		// send the message
		_tx16.setPayload(data);
		_tx16.setPayloadLength(dataLength);
		_xbee.send(_tx16);
	}
}

#endif