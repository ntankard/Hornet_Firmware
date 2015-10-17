#pragma once

#include <stdint.h>

/**
* \brief	A generic way of passing float arrays of variouse sizes
*/
class MessageBuffer_Passer
{
public:

	virtual volatile uint8_t getID()volatile = 0;
	virtual volatile uint8_t* getPacket()volatile = 0;
	virtual volatile int16_t* getData()volatile = 0;
	virtual volatile bool setPacket(uint8_t* data, int size) = 0;
	virtual volatile void setData(int16_t* data) = 0;
	virtual volatile void setSendCOunt(uint8_t count) = 0;
};