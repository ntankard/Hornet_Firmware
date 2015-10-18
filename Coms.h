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
	int getNORegisters();
	volatile MessageBuffer_Passer* getNextRegister();

	void send(volatile MessageBuffer_Passer* data);
	void send(uint8_t *data, uint8_t dataLength);

	bool run();

private:

	uint8_t _sendCount;

	int _readCount;
	uint8_t _checkSum;
	uint8_t _readMessage[MAX_PACKET_SIZE];
	
	ComsDecoder _comsDecoder;
};

