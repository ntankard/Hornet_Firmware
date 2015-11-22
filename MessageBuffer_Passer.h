#pragma once

#include <stdint.h>

/**
* \brief	A generic way of passing short arrays of various sizes
*/
class MessageBuffer_Passer
{
public:

	/**
	* \brief	Get the ID of the packet
	*
	* \return	The ID
	*/
	virtual uint8_t getID()volatile = 0;

	/**
	* \brief	Get the bytes to send as a com packet (including the \n)
	*
	* \return	an array of bytes of size getPacketSize()
	*/
	virtual volatile uint8_t* getPacket()volatile = 0;

	/**
	* \brief	Gets the number of bytes that will be sent as a packet
	*
	* \return	the number of bytes to send
	*/
	virtual int getPacketSize()volatile = 0;

	/**
	* \brief	Gets the payload data as shorts
	*
	* \return	the data
	*/
	virtual volatile int16_t* getData()volatile = 0;

	/**
	* \brief	Sets the value of the pacekt from a data stream received from the coms
	*
	* \param	data				An array of data that represents a packet	(excluding the \n)
	* \param	size				The number of bytes in the above array
	* \param	countedChecksum		The checksum caculated while the data was read
	*
	* \return	true if the data was valid and the value of this packet was updated
	*/
	virtual bool setPacket(uint8_t* data, int size, int countedChecksum)volatile = 0;

	/**
	* \brief	Sets the SendCount value of the packet (check is recaculated)
	*
	* \param	the count to set
	*/
	virtual void setSendCount(uint8_t count)volatile = 0;
};