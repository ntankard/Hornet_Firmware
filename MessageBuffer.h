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
		}packet ;
	};

	//-----------------------------------------------------------------------------------------------------------------------------

	MessageBuffer()
	{
		_message.value.comID = ID;
		_isLocked = false;
		_monitor = false;
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	
	volatile uint8_t getID()volatile
	{
		return _message.value.comID;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile uint8_t getComPri()volatile
	{
		return ComPri;
	}

	//------------------------------------------------------------ DATA ------------------------------------------------------------

	volatile int16_t* getData()volatile
	{
		return _message.value.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void copyData(int16_t* data)volatile
	{
		for (int i = 0; i < getDataSize(); i++)
		{
			getData()[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getDataSize()volatile
	{
		return Size;
	}

	//----------------------------------------------------------- BYTES ------------------------------------------------------------

	volatile uint8_t* getBytes()volatile
	{
		return _message.raw.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void copyBytes(uint8_t* data)volatile
	{
		for (int i = 0; i < getBytesSize(); i++)
		{
			getBytes()[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getBytesSize()volatile
	{
		return Size * sizeof(int16_t);
	}

	//----------------------------------------------------------- PACKET -----------------------------------------------------------

	volatile uint8_t* getPacket()volatile
	{
		return _message.packet.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void copyPacket(uint8_t* data)volatile
	{
		for (int i = 0; i < getPacketSize(); i++)
		{
			getPacket()[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getPacketSize()volatile
	{
		return Size * sizeof(int16_t) + 1;
	}

	//----------------------------------------------------------- LOCK -----------------------------------------------------------

	void lock()volatile
	{
		_isLocked = true;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void unlock()volatile
	{
		_isLocked = false;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile bool isLocked()volatile
	{
		return _isLocked;
	}

	//---------------------------------------------------------- MONITOR ----------------------------------------------------------

	void monitor()volatile
	{
		_monitor = true;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void dontMonitor()volatile
	{
		_monitor = false;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	volatile bool isMonitor()volatile
	{
		return _monitor;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

private:

	volatile  MemoryMap _message;
	volatile bool _isLocked;
	volatile bool _monitor;
};