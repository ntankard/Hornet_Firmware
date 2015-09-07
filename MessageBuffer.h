#pragma once

#include "MessageBuffer_Passer.h"

/**
* \brief	A dynamic size message container for int16_t
*
* \param	ID		The message ID
* \param	ComPri	The comunications prioroty of the message (if monitor is true)
* \param	Size	The number of int16_t in the message
*/
template<uint8_t ID, uint8_t ComPri, int Size>
class MessageBuffer : public MessageBuffer_Passer
{
public:

	typedef union MemoryMap
	{
		struct
		{
			uint8_t dump;	// needed to acoutn for arduino DUE page size (i think)
			uint8_t comID;
			int16_t data[Size];
		}value;
		struct
		{
			uint8_t dump;
			uint8_t comID;
			uint8_t data[Size * sizeof(int16_t)];
		}raw;
		struct
		{
			uint8_t dump;
			uint8_t data[Size * sizeof(int16_t) + 1];
		}packet;
	};

	//-----------------------------------------------------------------------------------------------------------------------------

	MessageBuffer()
	{
		_message.value.comID = ID;
		_isLocked = false;
		_monitor = false;
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	
	uint8_t getID()
	{
		return _message.value.comID;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	uint8_t getComPri()
	{
		return ComPri;
	}

	//------------------------------------------------------------ DATA ------------------------------------------------------------

	int16_t* getData()
	{
		return _message.value.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void copyData(int16_t* data)
	{
		for (int i = 0; i < getDataSize(); i++)
		{
			getData()[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getDataSize()
	{
		return Size;
	}

	//----------------------------------------------------------- BYTES ------------------------------------------------------------

	uint8_t* getBytes()
	{
		return _message.raw.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void copyBytes(uint8_t* data)
	{
		for (int i = 0; i < getBytesSize(); i++)
		{
			getBytes()[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getBytesSize()
	{
		return Size * sizeof(int16_t);
	}

	//----------------------------------------------------------- PACKET -----------------------------------------------------------

	uint8_t* getPacket()
	{
		return _message.packet.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void copyPacket(uint8_t* data)
	{
		for (int i = 0; i < getPacketSize(); i++)
		{
			getPacket()[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getPacketSize()
	{
		return Size * sizeof(int16_t) + 1;
	}

	//----------------------------------------------------------- LOCK -----------------------------------------------------------

	void lock()
	{
		_isLocked = true;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void unlock()
	{
		_isLocked = false;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	bool isLocked()
	{
		return _isLocked;
	}

	//---------------------------------------------------------- MONITOR ----------------------------------------------------------

	void monitor()
	{
		_monitor = true;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void dontMonitor()
	{
		_monitor = false;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	bool isMonitor()
	{
		return _monitor;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

private:

	MemoryMap _message;
	bool _isLocked;
	bool _monitor;
};