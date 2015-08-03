#pragma once

#include "XBee.h"
#include "ComsDecoder.h"

class Coms
{
public:
	Coms(ComsDecoder* comsDecoder);

	void run();

	bool canSend();

	void send(uint8_t *data, uint8_t dataLength);

private:
	
	
	ComsDecoder* _comsDecoder;

#if COM_MODE == COM_MODE_XBEE
	XBee _xbee;
	// resuse to save time
	Rx16Response _rx16;
	Tx16Request _tx16;
	TxStatusResponse _txStatus;

	// last message info
	int _resendCount;
	bool _outstandingSent;
#endif

#if COM_MODE == COM_MODE_SERIAL
	uint8_t _buffer[C_COMS_BUFFER];
	int _readData;
#endif

};

