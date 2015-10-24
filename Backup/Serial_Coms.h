#pragma once
#include "CONFIG.h"

#if COM_MODE == COM_MODE_SERIAL

#include "Coms.h"

/**
* \brief	Com system implimented over a USB serial port
*/
class Serial_Coms :public Coms
{
public:

	Serial_Coms(ComsDecoder* comsDecoder);
	bool start(){ return true; }
	void run();
	bool canSend();
	void send(uint8_t *data, uint8_t dataLength);

private:

	/** \brief	Storgae partialy read messages*/
	uint8_t _buffer[C_COMS_BUFFER];

	/** \brief	How many bytes in a message have been read */
	int _readData;
};

#endif