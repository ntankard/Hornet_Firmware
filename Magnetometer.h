#pragma once
#include "CONFIG.h"
#include "Runnable.h"
#include <Arduino.h>
#include "Error.h"
#include "Magnetometer.h"

#ifdef USE_MAG

#include "SPIManager.h"
#include "Error.h"

#include "MicroMag3.h"
#include "MovingAverage.h"
#include "CircularBuffer.h"
#include "MessageBuffer_Manager.h"

/**
* \brief	A mamanger for a MicroMag3 magnotomiter
*/
class Magnetometer :public Runnable
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	e					The hared error object
	*/
	Magnetometer(volatile Error *e);

	/**
	* \brief	Setupt the conection to the device
	*
	* \return	Was the device conected to sucsesfuly
	*/
	bool start();

	/**
	* \brief	Exicute a step in the operation of the magnotometer
	*
	* \throw	E_HARDWARE_FAILURE	If the read times out
	*/
	int run();

	volatile  MessageBuffer_Passer* getMessage()volatile;

private:

	volatile MessageBuffer_Passer* _toSend[2];

	int _sendCount;

	/** \brief	The fillter for the raw data */
	MovingAverage<float, C_YAW_WINDOW_AVE_WIDTH> _yawBuffer;

	/** \brief	The message buffers for Yaw data */
	volatile MessageBuffer_Manager<MB_YAW_SETTINGS> _yawSender;

	/** \brief	The message buffers for raw mag data */
	volatile MessageBuffer_Manager<MB_RAW_MAG_SETTING> _rawSender;

	/** \brief	The magnotomiter sensor */
	MicroMag3 _mag;
};

#else

class Magnetometer : public Runnable
{
public:

	Magnetometer(volatile Error *e){}
	bool start(){return true;}
	int run(){return 0;}
	volatile  MessageBuffer_Passer* getMessage()volatile{return NULL;}
};

#endif
