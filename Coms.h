#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "CONFIG.h"
#include "ComsDecoder.h"

#define COM_SERIAL Serial
//#define START_BYTE	0b10101010
//#define END_BYTE	0b10101010
#define END_BYTE	'\n'
#define MAX_PACKET_SIZE	50

class Coms
{
public:

	Coms();

	void send(volatile MessageBuffer_Passer* data);
	void send(uint8_t *data, uint8_t dataLength);

	int run();
	volatile MessageBuffer_Passer* getMessage()volatile { return _pendingMessage; }

private:

	uint8_t _sendCount;

	int _readCount;
	uint8_t _checkSum;
	uint8_t _readMessage[MAX_PACKET_SIZE];
	
	ComsDecoder _comsDecoder;

	volatile MessageBuffer_Passer* _pendingMessage;
	volatile MessageBuffer_Empty _pendingMessageDefault;
};

