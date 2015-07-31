#pragma once
#include "CONFIG.h"
#include <Arduino.h>

/**
 * \struct	ErrorMessage
 *
 * \brief	The information about a single error event
 *
 * \author	Nicholas
 * \date	1/08/2015
 */
struct ErrorMessage
{
	int errorCode;
	String errorInfo;
};

/**
 * \class	Error
 *
 * \brief	A collection of error events (used in place of exceptions)
 *
 * \author	Nicholas
 * \date	1/08/2015
 */
class Error
{
public:

	/**
	 * \fn	Error::Error();
	 *
	 * \brief	Default constructor.
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 */
	Error();

	/**
	 * \fn	void Error::add(int code, String info);
	 *
	 * \brief	Adds a error event (nothing is added if more than C_ERROR_BUFFER have been added befor)
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 *
	 * \param	code	The code.
	 * \param	info	The information.
	 */
	void add(int code, String info);

	/**
	 * \fn	bool Error::isError();
	 *
	 * \brief	Are there any recorded error events
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 *
	 * \return	true if error, false if not.
	 */
	bool isError();

	/**
	 * \fn	ErrorMessage* Error::getError();
	 *
	 * \brief	Gets the next error in the list (only call if isError return true)
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 *
	 * \return	null if it fails, else the error.
	 */
	ErrorMessage* getError();

private:

	/** \brief	The error events[ c error buffer]. */
	ErrorMessage _errorEvents[C_ERROR_BUFFER];

	/** \brief	The number of recorded errors */
	int _errors;
};

