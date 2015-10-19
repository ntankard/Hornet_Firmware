#pragma once

#include <stdint.h>

/**
* \brief	A generic way of passing float arrays of variouse sizes
*/
class MessageBuffer_Passer
{
public:

	virtual uint8_t getID()volatile = 0;
	virtual volatile uint8_t* getPacket()volatile = 0;
	virtual volatile int16_t* getData()volatile = 0;
	virtual bool setPacket(uint8_t* data, int size, int countedChecksum)volatile = 0;
	virtual void setData(int16_t* data)volatile = 0;
	virtual void setSendCount(uint8_t count)volatile = 0;
	virtual int getPacketSize()volatile = 0;
};