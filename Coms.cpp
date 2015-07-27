#include "Coms.h"
#include "ComsDecoder.h"

Coms::Coms(Stream &serial)
{
	uint8_t *data = new uint8_t();
	_xbee.begin(serial);
	_tx16 = Tx16Request(0x0000, data, 1);
	_outstandingSent = false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Coms::run()
{
	_xbee.readPacket();
	if (_xbee.getResponse().isAvailable())
	{
		if (_xbee.getResponse().getApiId() == RX_16_RESPONSE)
		{
			// new message
			_xbee.getResponse().getRx16Response(_rx16);
			ComsDecoder::processMessage(_rx16.getData(), _rx16.getDataLength());
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
				if (_resendCount >= 4)
				{
					ComsDecoder::sendFailure();
					_outstandingSent = false;
				}
			}
		}
		else
		{
			ComsDecoder::receiveFailure();
		}
	}
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

