#pragma once

#include "ComsDecoder.h"
#include "Runnable.h"

/**
* \brief	A abstract interaface for comunication with a base station
*/
class Coms:public Runnable
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	comsDecoder	The object to process incoming messages
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	Coms(ComsDecoder* comsDecoder);

	/**
	* \brief	Setupt the conection to the device
	*
	* \return	Was the device conected to sucsesfuly
	*/
	virtual bool start() = 0;

	/**
	* \brief	Exicute a step in the operation of the com
	*/
	virtual void run() = 0;

	/**
	* \brief	Check to see if the com system is clear for a new message
	*
	* \return   Can a message be sent
	*/
	virtual bool canSend() = 0;

	/**
	* \brief	Queue up a single message to be sent
	*
	* \param	data		The data to send
	* \param	dataLength	The number of bytes to send
	*/
	virtual void send(uint8_t *data, uint8_t dataLength) = 0;

protected:
	
	/** \brief	The object to process incoming messages */
	ComsDecoder* _comsDecoder;
};

