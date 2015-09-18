#pragma once

#include "MessageBuffer.h"
#include "MessageBuffer_Passer.h"

#include "CONFIG.h"

/**
* \brief	A manager for a set of Message Bufffers
*
* \param	MessageID	The message ID
* \param	MessageSize	The number of floats in the message
* \param	ToMonitor	How many messages need to be sent befor it should be send to the base station
* \param	ComPri		The comunications prioroty of the message (if monitor is true)
* \param	BufferSize	THe number of MessageBuffers to have
*/
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
	volatile MessageBuffer_Passer* getAvailable() volatile
	{
		bool safe = true;

		// find a free buffer
		volatile MessageBuffer_Passer* toSend = &_safe;
		for (int i = 0; i < BufferSize; i++)
		{
			if (!_message[i].isLocked())
			{
				toSend =  &_message[i];
				safe = false;
				break;
			}
		}

		if (safe == true)
		{
			//TP("OVERFLOW");
		}

		// should this message be monitored?
		_monitorCount++;
		if (ToMonitor != 0 && _monitorCount >= ToMonitor)
		{
			_monitorCount = 0;
			if (!safe)
			{
				toSend->monitor();
			}
			else
			{
				toSend->dontMonitor();
			}
			
		}
		else
		{
			toSend->dontMonitor();
		}

		return toSend; 
	}

private:

	/** \brief	How many messages have been sent wince the last one was monitord */
	int _monitorCount;

	/** \brief	A pool of avalible buffers to use */
	volatile MessageBuffer<MessageID, ComPri, MessageSize> _message[BufferSize];

	/** \brief	A object the can never be locked to ensure there is always avalible memory */
	volatile MessageBuffer<MessageID, ComPri, MessageSize> _safe;
};