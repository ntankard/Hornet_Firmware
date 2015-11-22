#pragma once

/**
* \brief	A Timer to detect timeout events
*/
class TimeOut
{
public:

	/**
	* \brief	Default constructor
	*/
	TimeOut();

	/**
	* \brief	Start a new timeout measure
	*
	* \param	duration	The time to wait before a timeout event
	*/
	void start(unsigned long duration);

	/**
	* \fn	bool Error::isError();
	*
	* \brief	Has more than duration time pass since the call of start
	*
	* \return	true if a timeout occured
	*/
	bool hasTimeOut();

private:

	/** \brief	The system time when the timout measure started */
	volatile unsigned long _startTime;

	/** \brief	THe duration before a timeout event */
	volatile unsigned long _duration;

	/** \brief	Has the time exceeded the duration? */
	bool _isTimeout;

};

