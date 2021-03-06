#pragma once
#include "Config.h"
#include "Runnable.h"
#include "Error.h"
#include "MessageBuffer.h"

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
	* \brief	Default constructor
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

	int getNORegisters();
	volatile MessageBuffer_Passer* getRegister();
	void addRegister(volatile MessageBuffer_Passer* newRegister);

	/**
	* \brief	Turn on (and reset) the indicator
	*/
	void on();

	/**
	* \brief	Turn off the indicator
	*/
	void off();

	/**
	* \brief	Set the display properties
	*
	* \param	setting_1	First light on
	* \param	setting_2	Second light on
	* \param	blinks		How many times to blink (eg. blink 3 times then a gap)
	* \param	rate		How fast to blink
	*/
	void setDisplay(int setting_1, int setting_2, int blinks, int rate);

	/**
	* \brief	Reassess the indicator and make any needed hardware changes
	*
	* \return	0 (never passes a message)
	*/
	bool run();


	/**
	* \brief	Switch on the safe light (a light that's not affected by the other blinking lights)
	*/
	void safeOn();

	/**
	* \brief	Switch off the safe light (a light that's not affected by the other blinking lights)
	*/
	void safeOff();

private:

	MessageBuffer<0, 1> _empty;

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

	/** \brief	How many times to blink (eg. blink 3 times then a gap) */
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


#endif
