#pragma once

/**
* \brief	A generic way of passing float arrays of variouse sizes
*/
class MessageBuffer_Passer
{
public:

	virtual float* getData() = 0;
	virtual void setData(float* data) = 0;
	virtual uint8_t* getBytes() = 0;
	virtual void setBytes(uint8_t* data) = 0;
	virtual int getSize() = 0;
	virtual uint8_t* getPacket();
	virtual int getPacketSize() = 0;
	virtual bool isLocked() = 0;
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual uint8_t getID() = 0;
	virtual uint8_t getComPri() = 0;
	virtual void monitor() = 0;
	virtual void dontMonitor() =0;
	virtual bool isMonitor() = 0;
};