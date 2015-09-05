#pragma once

//		 Rate * 2 * blinks
//	<---------------------------->
//
//	     ____      ____      ____                          ____      ____      ____
//	    | 1  |    | 2  |    | 3  |      1         2       | 1  |    | 2  |    | 3  |      1         2      
//	____|    |____|    |____|    |____ ____ ____ ____ ____|    |____|    |____|    |____ ____ ____ ____  
//
//		 <-->					 <------------------->
//	 	 Rate					Rate * 2 * gapMultiplye
//
//	blinks			= 3
//	gapMultiplyer	= 2


/**
* \brief	Generates a sequence of pulses (see ablove)
*/
class SequenceGenerator
{
public:

	/**
	* \brief	Default constructor.
	*/
	SequenceGenerator();

	/**
	* \brief	Sets the paramiters for the pulse
	*
	* \param	rate			The time between changes
	* \param	blinks			How many high periods per pulse set
	* \param	gapMultiplyer	How much longer should the gap be
	*/
	void set(unsigned long rate, unsigned blinks, unsigned gapMultiplyer);

	/**
	* \brief	Is the pulse currently high
	*
	* \return	true if the pulse is high
	*/
	bool isHigh();

	/**
	* \brief	Take a step in the pulse
	*
	* \return	true the pulse has changed (call is high after this)
	*/
	bool run();

private:

	/**
	* \brief	Take a step in a simple on off pulse
	*
	* \return	true the pulse has changed (call is high after this)
	*/
	bool runBlink();

	/**
	* \brief	Take a step in a full sequence
	*
	* \return	true the pulse has changed (call is high after this)
	*/
	bool runSequence();

	/**
	* \brief	Reset all variable used in the pulse
	*/
	void reset();

	/** \brief	the time of the last event */
	unsigned long _pastTime;

	/** \brief	How fast to blink */
	unsigned long _rate;

	/** \brief	How many times to blink (eg blink 3 times then a gap) */
	unsigned _blinks;

	/** \brief	How long should the gap be */
	unsigned _gapMultiplyer;

	/** \brief	are the lights on or off? */
	bool _isHigh;

	/** \brief	Is in the indicator in a bag between blinks*/
	bool _isBreak;

	/** \brief	how many blanks have alredy orcured (since the last break)*/
	unsigned _doneBlinks;
};

