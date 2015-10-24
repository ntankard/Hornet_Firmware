#pragma once
#include "Config.h"
#include "Runnable.h"
#include "Error.h"
#include "MessageBuffer.h"

#ifdef USE_RBG_INDICATOR

#include "SequenceGenerator.h"


#define NUM_LIGHTS 3
#define NUM_SETTINGS 4
#define SAFE_LIGHT	2	//RED

const int LIGHT_PINS[NUM_LIGHTS] = { RBG_GREEN, RBG_BLUE, RBG_RED };

const int SETIINGS[NUM_SETTINGS][NUM_LIGHTS - 1] = { {LOW,LOW},
													{ HIGH, LOW },			//GREEN
													{ LOW, HIGH },			//BLUE
													{ HIGH, HIGH }};		//CYAN


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
	int getNORegisters(){ return 0; }
	volatile MessageBuffer_Passer* getRegister(){ return &_empty; }
	void addRegister(volatile MessageBuffer_Passer* newRegister){}

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
	* \param	blinks		How many times to blink (eg blink 3 times then a gap)
	* \param	rate		How fast to blink
	*/
	void setDisplay(int setting, int blinks, int rate);

	/**
	* \brief	Reasses the indicator and make and needed harddware changed
	*
	* \return	0 (never passes a message)
	*/
	bool run();


	/**
	* \brief	Swich on the safe light (a light thats not effected by the otehr blinking lights)
	*/
	void safeOn();

	/**
	* \brief	Swich off the safe light (a light thats not effected by the otehr blinking lights)
	*/
	void safeOff();

private:

	MessageBuffer<0, 1> _empty;

	/**
	* \brief	Turn on a sequence of lights
	*
	* \param	setting	The coordinate of light one (x + ROWS*y)
	*/
	void lightOn(int setting);

	/**
	* \brief	Turn off a sequence of lights
	*/
	void lightOff();

	/** \brief	Is the indicator on */
	bool _isOn;

	/** \brief	How many times to blink (eg blink 3 times then a gap) */
	int _blinks;

	/** \brief	How fast to blink */
	unsigned long _rate;

	/** \brief	The coordinate of light 1 */
	int _setting;

	/** \brief	The shared error object */
	volatile Error *_e;

	/** \brief	The sequence generator */
	SequenceGenerator _sequenceGenerator;
};

#endif