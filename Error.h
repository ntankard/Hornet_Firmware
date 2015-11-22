#pragma once
#include "Config.h"
//#include "Arduino.h"
#include "stdint.h"

#define Throw_Check(toReturn)	if(_e->isError()){return toReturn;}
#define Could_Throw(function, toReturn)	function;if(_e->isError()){return toReturn;}

/**
 * \class	Error
 *
 * \brief	A collection of error events (used in place of exceptions)
 */
class Error
{
public:

	/**
	 * \fn	Error::Error();
	 *
	 * \brief	Default constructor
	 */
	Error();

	/**
	 * \fn	void Error::add(int code, String info);
	 *
	 * \brief	Adds an error event (nothing is added if more than C_ERROR_BUFFER have been added before)
	 *
	 * \param	code	The code
	 * \param	line	The line that the error occurred on
	 */
	void add(uint8_t code, uint8_t  line) volatile;

	/**
	 * \fn	bool Error::isError();
	 *
	 * \brief	Are there any recorded error events
	 *
	 * \return	true if error, false if not
	 */
	bool isError() volatile;

	/**
	 * \fn	ErrorMessage* Error::getError();
	 *
	 * \brief	Gets the next error in the list (only call if isError return true)
	 *
	 * \return	null if it fails, else the error
	 */
	uint16_t getError() volatile;

private:

	/** \brief	The error events[ c error buffer] */
	uint8_t _errorEvents[C_ERROR_BUFFER];

	/** \brief	THe line that the error occurred on */
	uint8_t _errorLine[C_ERROR_BUFFER];

	/** \brief	The number of recorded errors */
	int _errors;
};

