#pragma once
#include "Config.h"
#include "Runnable.h"
#include "Error.h"

#ifdef USE_DM_INDICATOR

#include "SequenceGenerator.h"

const int ROWS[] = { CANODE_6, CANODE_10, CANODE_11, CANODE_3, CANODE_13 };
const int COLUMNS[] = { CANODE_9, CANODE_14, CANODE_8, CANODE_12, CANODE_1, CANODE_7, CANODE_2 };

#define NUM_ROWS 5
#define NUM_COLLUNS 7

const int MATRIX_SIZE = ((NUM_ROWS - 1) * (NUM_COLLUNS - 1));

#define ROW_ON HIGH
#define ROW_OFF LOW
#define COLUMNS_ON LOW
#define COLUMNS_OFF HIGH


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
	bool start();

	void safeOn();
	void safeOff();
	void reset();
private:


	void lightOn(int setting_1, int setting_2);
	void lightOff(int setting_1, int setting_2);

	/** \brief	Is the indicator on */
	bool _isOn;

	/** \brief	How many times to blink (eg blink 3 times then a gap) */
	int _blinks;

	/** \brief	How fast to blink */
	unsigned long _rate;

	/** \brief	setting	What to display  (eg color for the APM) */
	int _setting_1;
	int _setting_2;


	Error *_e;

	SequenceGenerator _sequenceGenerator;
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
