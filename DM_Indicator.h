#pragma once
#include "Config.h"
#include "Runnable.h"
#include "Error.h"

#ifdef USE_DM_INDICATOR

#include "SequenceGenerator.h"

#define NUM_ROWS 5
#define NUM_COLLUNS 7

const int ROWS[NUM_ROWS] = { CANODE_6, CANODE_10, CANODE_11, CANODE_3, CANODE_13 };
const int COLUMNS[NUM_COLLUNS] = { CANODE_9, CANODE_14, CANODE_8, CANODE_12, CANODE_1, CANODE_7, CANODE_2 };
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
	Indicator(volatile Error *e);

	/**
	* \brief	Setup all the pins for the indicator 
	*
	* \return	always true (no hardware check)
	*/
	bool start();

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
	* \return	0 (never passes a message)
	*/
	int run();

	/**
	* \brief	Unimplimented
	*/
	volatile MessageBuffer_Passer* getMessage()volatile { return NULL; }

	/**
	* \brief	Swich on the safe light (a light thats not effected by the otehr blinking lights)
	*/
	void safeOn();

	/**
	* \brief	Swich off the safe light (a light thats not effected by the otehr blinking lights)
	*/
	void safeOff();

private:

	/**
	* \brief	Turn on a sequence of lights
	*
	* \param	setting_1	The coordinate of light one (x + ROWS*y)
	* \param	setting_2	The coordinate of light two (x + ROWS*y)
	*/
	void lightOn(int setting_1, int setting_2);

	/**
	* \brief	Turn off a sequence of lights
	*
	* \param	setting_1	The coordinate of light one (x + ROWS*y)
	* \param	setting_2	The coordinate of light two (x + ROWS*y)
	*/
	void lightOff(int setting_1, int setting_2);

	/** \brief	Is the indicator on */
	bool _isOn;

	/** \brief	How many times to blink (eg blink 3 times then a gap) */
	int _blinks;

	/** \brief	How fast to blink */
	unsigned long _rate;

	/** \brief	The coordinate of light 1 */
	int _setting_1;

	/** \brief	The coordinate of light 2 */
	int _setting_2;

	/** \brief	The shared error object */
	volatile Error *_e;

	/** \brief	The sequence generator */
	SequenceGenerator _sequenceGenerator;
};

#else
class Indicator :public Runnable{
public:
	Indicator(volatile Error *e){}
	bool start(){return false;}
	void on(){}
	void off(){}
	void setDisplay(int setting_1, int setting_2, int blinks, int rate){}
	int run(){return 0;}
	volatile MessageBuffer_Passer* getMessage()volatile { return NULL; }
	void safeOn(){}
	void safeOff(){}
};
#endif
