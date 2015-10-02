#pragma once

#include "Runnable.h"
#include "Serial_Coms.h"
#include "XBee_Coms.h"
#include "Error.h"
#include "MessageBuffer_Passer.h"
#include "CircularBuffer_Manager.h"
#include "Coms.h"

/**
* \brief	An object to buffer messages for sending
*/
class ComsEncoder:public Runnable
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	coms	The object to send messages
	* \param	e		The shared error object
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	ComsEncoder(volatile Error *e);

	/**
	* \brief	Sends one of the waiting messages
	*/
	int run();
	volatile MessageBuffer_Passer* getMessage()volatile { return _toReturn; }

	/**
	* \brief	DO NOTHING
	*/
	bool start(){ return true; }

	/**
	* \brief	Add one message to the queue
	*
	* \param	data	The message to send
	*
	* \return	Was there enough room in the buffers to send the message
	*/
	bool sendData(volatile MessageBuffer_Passer *data);

	/**
	* \brief	Add a single char to the queu (top priority)
	*
	* \param	message	The message to send
	*
	* \return	Was there enough room in the buffers to send the message
	*/
	bool sendChar(uint8_t message);

private:

	/** \brief	The object to send messages */
	Coms _coms;

	/** \brief	The shared error object */
	volatile Error *_e;

	/** \brief	The buffer of messages to send */
	volatile MessageBuffer_Passer* _buffer[C_CL][C_COMENCODER_SIZE];

	/** \brief	The manger for the queue of messages */
	CircularBuffer_Manager<C_COMENCODER_SIZE> _buffer_man[C_CL];

	
	
	/** \brief	The buffer of bytes to send */
	uint8_t _messageBuffer[C_COMENCODER_M_SIZE];

	/** \brief	The manager for the byte buffer */
	CircularBuffer_Manager<C_COMENCODER_M_SIZE> _messageBuffer_man;

	volatile MessageBuffer_Passer* _toReturn;
};

