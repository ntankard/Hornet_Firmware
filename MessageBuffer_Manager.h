#pragma once

#include "MessageBuffer.h"
#include "MessageBuffer_Passer.h"
#include "CircularBuffer_Manager.h"


template<uint8_t MessageID, int MessageSize, int ToMonitor, uint8_t ComPri, int BufferSize>
class MessageBuffer_Manager
{
public:

	/**
	* \brief	Default constructor.
	*/
	MessageBuffer_Manager()
	{
		_safe.lock();	// ensure that no object cant ever lock this object
		_monitorCount = 0;
	}

	/**
	* \brief	Gets ana avalible buffer from the pool
	*
	* \return	An avalible buffer
	*/
	MessageBuffer_Passer* getAvailable()
	{
		// find a free buffer
		MessageBuffer_Passer* toSend = &_safe;
		for (int i = 0; i < BufferSize; i++)
		{
			if (!_message[i].isLocked())
			{
				toSend =  &_message[i];
			}
		}

		// should this message be monitored?
		_monitorCount++;
		if (ToMonitor != 0 && _monitorCount >= ToMonitor)
		{
			_monitorCount = 0;
			toSend->monitor();
		}
		else
		{
			toSend->dontMonitor();
		}

		return toSend; 
	}

private:

	int _monitorCount;

	/** \brief	A pool of avalible buffers to use */
	MessageBuffer<MessageID, ComPri, MessageSize> _message[BufferSize];

	/** \brief	A object the can never be locked to ensure there is always avalible memory */
	MessageBuffer<MessageID, ComPri, MessageSize> _safe;
};