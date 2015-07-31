#include "Coms.h"
#include "ComsDecoder.h"
#include "CONFIG.h"
#include "Arduino.h"



Coms::Coms(ComsDecoder* comsDecoder)
{
	// setupt the object to notify on incoming messages
	_comsDecoder = comsDecoder;

	// create a resusable TX packet to save space
#if COM_MODE == COM_MODE_XBEE
	uint8_t *data = new uint8_t();
	_tx16 = Tx16Request(C_COMMS_BSTATION_ADDRESS, data, 1);

	// setup the conection to the XBEE
	C_COMS_PORT.begin(C_COMS_BAUD_RATE);
	_xbee.begin(C_COMS_PORT);
	_outstandingSent = false;
#endif

#if COM_MODE == COM_MODE_SERIAL
	C_COMS_PORT.begin(C_COMS_BAUD_RATE);
#endif

}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Coms::run()
{
#if COM_MODE == COM_MODE_XBEE
	_xbee.readPacket();
	if (_xbee.getResponse().isAvailable())
	{
		if (_xbee.getResponse().getApiId() == RX_16_RESPONSE)
		{
			// new message
			_xbee.getResponse().getRx16Response(_rx16);
			_comsDecoder->processMessage(_rx16.getData(), _rx16.getDataLength());
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
					_comsDecoder->sendFailure();
					_outstandingSent = false;
				}
			}
		}
		else
		{
			_comsDecoder->receiveFailure();
		}
	}
#endif
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Coms::canSend()
{
#if COM_MODE == COM_MODE_XBEE
	return !_outstandingSent;
#endif
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Coms::send(uint8_t *data, uint8_t dataLength)
{
#if COM_MODE == COM_MODE_XBEE
	if (!_outstandingSent)
	{
		_resendCount = 0;
		_outstandingSent = true;

		// send the message
		_tx16.setPayload(data);
		_tx16.setPayloadLength(dataLength);
		_xbee.send(_tx16);
	}
#endif
#if COM_MODE == COM_MODE_SERIAL
	for (int i = 0; i < dataLength; i++)
	{
		C_COMS_PORT.write(data[i]);
	}
	C_COMS_PORT.write("\n");
#endif
}

