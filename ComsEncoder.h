#pragma once

#include "CONFIG.h"
#include "Runnable.h"
#include "Error.h"
#include "MessageBuffer_Passer.h"
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
	* \param	e		The shared error object
	*/
	ComsEncoder(volatile Error *e);

	int getNORegisters();
	volatile MessageBuffer_Passer* getRegister();
	void addRegister(volatile MessageBuffer_Passer* newRegister);

	bool start();

	/**
	* \brief	Sends one of the waiting messages
	*/
	bool run();



private:

	/** \brief	The object to send messages */
	Coms _coms;

	/** \brief	The shared error object */
	volatile Error *_e;

	volatile MessageBuffer_Passer* _internalRegisters[MB_OUTBOUND_COUTN];
	bool _internalRegisters_addCount[MB_OUTBOUND_COUTN];

	int _sendId;
};


















/**
* \brief	Add a single char to the queu (top priority)
*
* \param	message	The message to send
*
* \return	Was there enough room in the buffers to send the message
*/
//bool sendChar(uint8_t message);

/** \brief	The buffer of messages to send */
//volatile MessageBuffer_Passer* _buffer[C_CL][C_COMENCODER_SIZE];

/** \brief	The manger for the queue of messages */
//CircularBuffer_Manager<C_COMENCODER_SIZE> _buffer_man[C_CL];



/** \brief	The buffer of bytes to send */
//uint8_t _messageBuffer[C_COMENCODER_M_SIZE];

/** \brief	The manager for the byte buffer */
//CircularBuffer_Manager<C_COMENCODER_M_SIZE> _messageBuffer_man;