#pragma once
#include "CONFIG.h"
#include "ComsDecoder.h"
#include "Runnable.h"

#ifdef USER_SERIAL_COMS

/**
* \brief	Com system implimented over a USB serial port
*/
class Coms :public Runnable
{
public:

	Coms();
	bool start(){ return true; }
	int run();
	bool canSend();
	void send(uint8_t *data, uint8_t dataLength);
	volatile MessageBuffer_Passer* getMessage()volatile { return _pendingMessage; }

private:

	/** \brief	Storgae partialy read messages*/
	uint8_t _buffer[C_COMS_BUFFER];

	/** \brief	How many bytes in a message have been read */
	int _readData;

	ComsDecoder _comsDecoder;

	volatile MessageBuffer_Passer* _pendingMessage;
};

#endif