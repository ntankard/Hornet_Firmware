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
	
	XBee _xbee;
	ComsDecoder* _comsDecoder;

	// resuse to save time
	Rx16Response _rx16;
	Tx16Request _tx16;
	TxStatusResponse _txStatus;

	// last message info
	int _resendCount;
	bool _outstandingSent;
};

