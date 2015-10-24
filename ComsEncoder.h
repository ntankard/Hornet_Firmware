#pragma once

#include "CONFIG.h"
#include "Runnable.h"
#include "Error.h"
#include "MessageBuffer_Passer.h"
#include "Coms.h"
#include "TimeOut.h"

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

	MessageBuffer<0, 1> _empty[MB_OUTBOUND_COUTN];
	volatile MessageBuffer_Passer* _internalRegisters[MB_OUTBOUND_COUTN];
	bool _internalRegisters_addCount[MB_OUTBOUND_COUTN];

	int _sendId;

	TimeOut _throttle;
};