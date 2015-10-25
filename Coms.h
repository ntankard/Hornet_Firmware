#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "CONFIG.h"
#include "ComsDecoder.h"
#include "Error.h"

#define END_BYTE		'\n'
#define MAX_PACKET_SIZE	50

class Coms
{
public:

	Coms(volatile Error *e);
	int getNORegisters();
	volatile MessageBuffer_Passer* getNextRegister();

	void send(volatile MessageBuffer_Passer* data);
	void send(uint8_t *data, uint8_t dataLength);

	bool run();

	int getSendCount(){ return _totalSend; }
	void setSendCound(int toSet){ _totalSend = toSet; }

private:

	uint8_t _sendCount;

	int _totalSend;
	int _readCount;
	uint8_t _checkSum;
	uint8_t _readMessage[MAX_PACKET_SIZE];
	
	ComsDecoder _comsDecoder;
};

