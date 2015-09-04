#pragma once
#include "Config.h"
#include "Runnable.h"
#include "Error.h"

#ifdef USE_DM_INDICATOR


class Indicator : public Runnable
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	e	The shared error object
	*/
	Indicator(Error *e);

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
	* \param	setting_1	First light on
	* \param	setting_2	Second light on
	* \param	blinks		How many times to blink (eg blink 3 times then a gap)
	* \param	rate		How fast to blink
	*/
	void setDisplay(int setting_1, int setting_2, int blinks, int rate);

	/**
	* \brief	Reasses the indicator and make and needed harddware changed
	*
	* \author	Nicholas
	* \date	1/08/2015
	*/
	void run();

	// no implimented
	bool start(){ return true; }

	void safeOn();
	void safeOff();
private:
	void reset();

	void lightOn(int setting_1, int setting_2);
	void lightOff();

	/** \brief	Is the indicator on */
	bool _isOn;

	/** \brief	How many times to blink (eg blink 3 times then a gap) */
	int _blinks;

	/** \brief	How fast to blink */
	unsigned long _rate;

	/** \brief	setting	What to display  (eg color for the APM) */
	int _setting_1;
	int _setting_2;

	/** \brief	the time of the last event */
	unsigned long _pastTime;

	/** \brief	are the lights on or off? */
	bool _pinIsOn;

	/** \brief	Is in the indicator in a bag between blinks*/
	bool _isBreak;

	/** \brief	how many blanks have alredy orcured (since the last break)*/
	int _doneBlinks;

	Error *_e;
};

#else
class Indicator :public Runnable{
public:
	Indicator(){}
	void run(){}
	void on(){}
	void off(){}
	void setDisplay(int setting, int blinks, int rate);
};
#endif
