#pragma once
#include <inttypes.h>

#include "MessageBuffer.h"
#include "CONFIG.h"

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

	int getNORegisters();

	volatile MessageBuffer_Passer* getNextRegister();

	/**
	* \brief	Process a new incoming message
	*
	* \param	data		The received message
	* \param	dataLength	The number of bytes received
	*/
	bool processMessage(uint8_t *data, uint8_t dataLength, uint8_t checksum);

	/**
	* \brief	A message failed to be sent corectly
	*/
	void sendFailure();

	/**
	* \brief	A message was received corupt
	*/
	void receiveFailure();

private:

	volatile MessageBuffer<MB_JOY_THROTTLE, 1> _throttleJoyRegister;
	volatile MessageBuffer<MB_JOY_XY, 2> _XYJoyRegister;
	volatile MessageBuffer<MB_JOY_Z, 1> _ZJoyRegister;
	volatile MessageBuffer<MB_ARM_DISARM, 1> _ArmDisarmRegister;

	volatile MessageBuffer_Passer*	_registers[MB_INBOUND_COUNT];

	int _registerAccsessed;
};

