#pragma once

#include "MessageBuffer_Passer.h"

/**
* \brief	A dynamic size message container for int16_t
*
* \param	ID		The message ID
* \param	ComPri	The comunications prioroty of the message (if monitor is true)
* \param	Size	The number of int16_t in the message
*/
template<uint8_t theID, int Size>
class MessageBuffer : public MessageBuffer_Passer
{
public:

	typedef union MemoryMap
	{
		struct
		{
			uint8_t dump;	// needed to acoutn for arduino DUE page size (i think)
			uint8_t length;
			uint8_t count;
			uint8_t ID;
			int16_t data[Size];
			uint8_t check;
			uint8_t EOM;
		}value;
		struct
		{
			uint8_t dump;
			uint8_t data[(Size * sizeof(int16_t)) + 4];
		}packet;
	};

	//-----------------------------------------------------------------------------------------------------------------------------

	MessageBuffer()
	{
		_message.value.comID = theID;
		_message.value.length = (Size * 2) + 3;
		_message.value.EOM = '\n';
		for (int i = 0; i < Size; i++)
		{
			_message.value.data[i] = 0;
		}
		_message.value.check = getCheckSum();
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	
	volatile uint8_t getID()volatile
	{
		return _message.value.comID;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile uint8_t* getPacket()volatile
	{
		return _message.packet.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile int16_t* getData()volatile
	{
		return _message.value.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile bool setPacket(uint8_t* data, int size)
	{
		// validate size for the file type
		if (size != ((Size * sizeof(int16_t)) + 4))
		{
			return false;
		}

		// validate size against the packets reported length
		if (data[1] != ((Size * sizeof(int16_t)) + 1))
		{
			return false;
		}

		// validate the ID 
		if (data[2] != _message.value.ID)
		{
			return false;
		}

		// validate the checksum
		if (getCheckSum(data) != data[((Size * sizeof(int16_t)) + 3)])
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

	volatile void setData(int16_t* data)
	{
		for (int i = 0; i < Size; i++)
		{
			_message.value.data[i] = data[i];
		}
		_message.value.check = getCheckSum();
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile void setSendCOunt(uint8_t count)
	{
		_message.value.check -= _message.value.count * 2;
		_message.value.count = count;
		_message.value.check += _message.value.count * 2;
	}

private:

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile uint8_t getCheckSum()volatile
	{
		uint8_t check;
		for (int i = 0; i < ((Size * sizeof(int16_t)) + 4); i++)
		{
			check += _message.packet.data[i] * (i + 1);
		}
		return check;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile uint8_t getCheckSum(uint8_t* data)volatile
	{
		uint8_t check;
		for (int i = 0; i < ((Size * sizeof(int16_t)) + 4); i++)
		{
			check += data[i] * (i + 1);
		}
		return check;
	}

	volatile  MemoryMap _message;

};