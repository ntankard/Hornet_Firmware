#pragma once
#if ENABLE_INDICATOR == ENABLED

/**
* \brief	Uses some form of visual display to depict a message to the user
*/
class Indicator 
{
public:

	/**
	* \brief	Default constructor.
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	Indicator();

	/**
	* \brief	Turn on (and reset) the indicator
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	void on();

	/**
	* \brief	Turn off the indicator
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	void off();

	/**
	* \brief	Set the display properties
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \param	setting	What to display  (eg color for the APM)
	* \param	blinks	How many times to blink (eg blink 3 times then a gap)
	* \param	rate	How fast to blink
	*/
	void setDisplay(int setting, int blinks, int rate);

	/**
	* \brief	Reasses the indicator and make and needed harddware changed
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	void run();

protected:

	/**
	* \brief	Swich on the display
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \param	setting	What to display  (eg color for the APM)
	*/
	virtual void lightOn(int setting) = 0;

	/**
	* \brief	Swich of the display
	*
	* \author	Nicholas
	* \date	1/08/2015
	*
	* \param	setting	What to display  (eg color for the APM)
	*/
	virtual void lightOff() = 0;

	/** \brief	Is the indicator on */
	bool _isOn;


	/** \brief	How many times to blink (eg blink 3 times then a gap) */
	int _blinks;

	/** \brief	How fast to blink */
	unsigned long _rate;

	/** \brief	setting	What to display  (eg color for the APM) */
	int _setting;

	/** \brief	the time of the last event */
	unsigned long _pastTime;

	/** \brief	are the lights on or off? */
	bool _pinIsOn;

	/** \brief	Is in the indicator in a bag between blinks*/
	bool _isBreak;

	/** \brief	how many blanks have alredy orcured (since the last break)*/
	int _doneBlinks;
};

#else

class Indicator {
public:
	Indicator(){}
	void run(){}
	void on(){}
	void off(){}
	void setDisplay(int setting, int blinks, int rate);
};

#endif


