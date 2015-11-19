#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "CONFIG.h"
#include "ComsDecoder.h"
#include "Error.h"

#define END_BYTE		'\n'
#define MAX_PACKET_SIZE	50

/**
* \class	Coms
*
* \brief	Manages serial comuncication
*/
class Coms
{
public:

	Coms(volatile Error *e);

	// standard runnable methods
	int getNORegisters();
	volatile MessageBuffer_Passer* getNextRegister();
	bool run();
	int getSendCount(){ return _totalSend; }

	void send(volatile MessageBuffer_Passer* data);
	void send(uint8_t *data, uint8_t dataLength);

	void setSendCound(int toSet){ _totalSend = toSet; }

private:

	/** \brief	Rolling count of sent packets used to check for packet loss */
	uint8_t _sendCount;

	/** \brief	Number of packets send (used to monitor transmition rate) */
	int _totalSend;

	/** \brief	The number of bytes read for the current packet */
	int _readCount;

	/** \brief	The real time caculated checksum */
	uint8_t _checkSum;

	/** \brief	The partial message */
	uint8_t _readMessage[MAX_PACKET_SIZE];
	
	/** \brief	The object to decode incoming messages */
	ComsDecoder _comsDecoder;
};

