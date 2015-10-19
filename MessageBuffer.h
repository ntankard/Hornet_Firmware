#pragma once

#include "MessageBuffer_Passer.h"

/**
* \brief	A dynamic size message container for int16_t
*
* \param	THE_ID			The message ID
* \param	PAYLOAD_SIZE	The number of int16_t in the message
*/
template<uint8_t THE_ID, int PAYLOAD_SIZE>
class MessageBuffer : public MessageBuffer_Passer
{
public:

	static const int PACKET_SIZE_OUT = (PAYLOAD_SIZE * sizeof(int16_t)) + 5;
	static const int PACKET_SIZE_IN = (PAYLOAD_SIZE * sizeof(int16_t)) + 4;

	typedef union MemoryMap
	{
		struct
		{
			uint8_t dump;	// needed to acoutn for arduino DUE page size (i think)
			uint8_t length;
			uint8_t count;
			uint8_t ID;
			int16_t data[PAYLOAD_SIZE];
			uint8_t check;
			uint8_t EOM;
		}value;
		struct
		{
			uint8_t dump;
			uint8_t data[PACKET_SIZE_OUT];
		}packet;
	};

	//-----------------------------------------------------------------------------------------------------------------------------

	MessageBuffer()
	{
		_message.value.ID = THE_ID;
		_message.value.length = (PAYLOAD_SIZE * 2) + 1;
		_message.value.EOM = '\n';
		_message.value.count = 0;
		for (int i = 0; i < PAYLOAD_SIZE; i++)
		{
			_message.value.data[i] = 0;
		}
		_message.value.check = getCheckSum();
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	
	uint8_t getID()volatile
	{
		return _message.value.ID;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile uint8_t* getPacket()volatile
	{
		_message.value.check = getCheckSum();
		return _message.packet.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile int16_t* getData()volatile
	{
		return _message.value.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	bool setPacket(uint8_t* data, int size, int countedChecksum)volatile
	{
		// validate size for the file type
		if (size != PACKET_SIZE_IN)
		{
			return false;
		}

		// validate size against the packets reported length
		if (data[1] != ((PAYLOAD_SIZE * sizeof(int16_t)) + 1))
		{
			return false;
		}

		// validate the ID 
		if (data[2] != _message.value.ID)
		{
			return false;
		}

		// validate the checksum
		if (countedChecksum != data[PACKET_SIZE_IN -1])
		{
			return false;
		}

		// all checks pass, update the data
		for (int i = 0; i < size; i++)
		{
			_message.packet.data[i] = data[i];
		}

		return true;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void setSendCount(uint8_t count)volatile
	{
		_message.value.check -= _message.value.count * 2;
		_message.value.count = count;
		_message.value.check += _message.value.count * 2;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getPacketSize()volatile
	{
		return PACKET_SIZE_OUT;
	}

private:

	//-----------------------------------------------------------------------------------------------------------------------------

	uint8_t getCheckSum()volatile
	{
		uint8_t check =0;
		for (int i = 0; i < (PACKET_SIZE_IN - 1); i++)
		{
			check += _message.packet.data[i] * (i + 1);
		}
		return check;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile  MemoryMap _message;

};