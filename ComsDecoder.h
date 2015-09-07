#pragma once
#include <inttypes.h>

#include "MessageBuffer_Empty.h"



class HornetManager;

/**
* \brief	An object to process incoming messages
*/
class ComsDecoder
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	theManager	The message router
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	ComsDecoder();

	/**
	* \brief	Process a new incoming message
	*
	* \param	data		The received message
	* \param	dataLength	The number of bytes received
	*/
	MessageBuffer_Passer* processMessage(uint8_t *data, uint8_t dataLength);

	/**
	* \brief	A message failed to be sent corectly
	*/
	void sendFailure();

	/**
	* \brief	A message was received corupt
	*/
	void receiveFailure();

private:

	// reusable message buffer
	MessageBuffer_Empty _charMessage;
};

