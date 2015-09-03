#include "Error.h"

Error::Error()
{
	_errors = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Error::add(int code, String info)
{
	if (_errors >= (C_ERROR_BUFFER - 1))
	{
		// no more room (were in big troble)
		return;
	}

	_errorEvents[_errors].errorCode = code;
	_errorEvents[_errors].errorInfo = info;

	_errors++;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Error::isError()
{
	if (_errors == 0)
	{
		return false;
	}
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ErrorMessage* Error::getError()
{
	_errors--;

	return &_errorEvents[_errors + 1];
}
