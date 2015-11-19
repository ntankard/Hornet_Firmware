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

	// standard runnable functions
	int getNORegisters();
	volatile MessageBuffer_Passer* getRegister();
	void addRegister(volatile MessageBuffer_Passer* newRegister);
	bool start();
	bool run();

	/**
	* \brief	Get the number of messages sent for preformance tracking
	*
	* \return	The number of messages sent
	*/
	int getSendCount(){ return _coms.getSendCount(); }

	/**
	* \brief	Reset the send counter
	*
	* \param	toSet		The value to set
	*/
	void setSendCound(int toSet){ _coms.setSendCound(toSet); }
	

private:

	/** \brief	The object to send messages */
	Coms _coms;

	/** \brief	The shared error object */
	volatile Error *_e;

	/** \brief	An empty message buffer to put in place untill the real ones are attached */
	MessageBuffer<0, 1> _empty[MB_OUTBOUND_COUTN];

	/** \brief	A list of all internal messages */
	volatile MessageBuffer_Passer* _internalRegisters[MB_OUTBOUND_COUTN];

	/** \brief	Track what messages have been added */
	bool _internalRegisters_addCount[MB_OUTBOUND_COUTN];

	/** \brief	Track wich message to send */
	int _sendId;

	/** \brief	Timer to limit sending */
	TimeOut _throttle;
};