#pragma once
#include <inttypes.h>

#include "MessageBuffer_Empty.h"
#include "MessageBuffer_Manager.h"
#include "CONFIG.h"



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
	volatile MessageBuffer_Passer* processMessage(uint8_t *data, uint8_t dataLength);

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
	volatile MessageBuffer_Empty _charMessage;

	volatile MessageBuffer_Manager<MB_JOY_XY_SETTING> _XYJoySender;
	volatile MessageBuffer_Manager<MB_JOY_THROTTLE_SETTING> _throttleJoySender;
	volatile MessageBuffer_Manager<MB_JOY_Z_SETTING> _ZJoySender;

	volatile MessageBuffer_Manager<MB_ARM_DISARM_SETTING> _ArmDisarmSender;

	int test;

};

