#pragma once

#include <stdint.h>

/**
* \brief	A generic way of passing float arrays of variouse sizes
*/
class MessageBuffer_Passer
{
public:

	virtual volatile uint8_t getID()volatile = 0;
	virtual volatile uint8_t getComPri()volatile = 0;

	virtual volatile  int16_t* getData() volatile = 0;
	virtual void copyData(int16_t* data)volatile = 0;
	virtual int getDataSize()volatile = 0;
	virtual volatile uint8_t* getBytes()volatile = 0;
	virtual void copyBytes(uint8_t* data)volatile = 0;
	virtual int getBytesSize()volatile = 0;
	virtual volatile uint8_t* getPacket()volatile;
	virtual void copyPacket(uint8_t* data)volatile = 0;
	virtual int getPacketSize()volatile = 0;
	
	virtual void lock()volatile = 0;
	virtual void unlock()volatile = 0;
	virtual volatile  bool isLocked()volatile = 0;
	
	virtual void monitor()volatile = 0;
	virtual void dontMonitor()volatile = 0;
	virtual volatile bool isMonitor()volatile = 0;
};