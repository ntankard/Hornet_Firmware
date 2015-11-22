#pragma once
#include "MessageBuffer_Passer.h"

/**
* \class	Runnable
*
* \brief	A generic interface for a runnable object, runnable objects behave like threads
*/
class Runnable
{
public:

	/**
	* \brief	How many registers does this runnable object have?
	*
	* \return	The number of runnable objecs
	*/
	virtual int getNORegisters() = 0;

	/**
	* \brief	Gets the next register (will be called as many times as getNORegisters()
	*
	* \return	The next register
	*/
	virtual volatile MessageBuffer_Passer* getRegister() = 0;

	/**
	* \brief	Passes a link to a register owned by another object, if the runnable needs data from that register then this pointer should be stored
	*
	* \param	newRegister	The register to add
	*/
	virtual void addRegister(volatile MessageBuffer_Passer* newRegister) = 0;

	/**
	* \brief	Perform all thread start procedures
	*
	* \return	True if the thread started successfuly
	*/
	virtual bool start()  = 0;

	/**
	* \brief	Execute one loop of the thread
	*
	* \return	True if the value of a register was changed
	*/
	virtual bool run() = 0;
};

