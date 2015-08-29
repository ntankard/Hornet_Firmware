#pragma once

#include "MessageBuffer.h"
#include "MessageBuffer_Passer.h"
#include "CircularBuffer_Manager.h"

template<int MessageSize, int MessageID, int BufferSize>
class MessageBuffer_Manager
{
public:

	/**
	* \brief	Default constructor.
	*/
	MessageBuffer_Manager()
	{
		_safe.lock();	// ensure that no object cant ever lock this object
	}

	/**
	* \brief	Gets ana avalible buffer from the pool
	*
	* \return	An avalible buffer
	*/
	MessageBuffer_Passer* getAvailable()
	{
		for (int i = 0; i < BufferSize; i++)
		{
			if (!_message[i].isLocked())
			{
				return &_message[i];
			}
		}
		return &_safe;
	}

private:

	/** \brief	A pool of avalible buffers to use */
	MessageBuffer<MessageSize, MessageID> _message[BufferSize];

	/** \brief	A object the can never be locked to ensure there is always avalible memory */
	MessageBuffer<MessageSize, MessageID> _safe;
};