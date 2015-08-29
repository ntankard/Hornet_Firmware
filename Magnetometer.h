#pragma once
#include "CONFIG.h"
#include "Runnable.h"
#include "SPIManager.h"
#include "Error.h"
#include "HornetManager.h"

#if ENABLE_MAG == ENABLED

#include "MicroMag3.h"
#include "MovingAverage.h"
#include "MessageBuffer.h"
#include "CircularBuffer.h"

/**
* \brief	A mamanger for a MicroMag3 magnotomiter
*/
class Magnetometer : public Runnable
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	theHornetManager	The systems message router
	* \param	theSPIManager		THe SPI object to use to comunicate with the device
	* \param	e					The hared error object
	*/
	Magnetometer(HornetManager* theHornetManager,SPIManager *theSPIManager, Error *e);

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
	void run();

private:

	/** \brief	The magnotomiter sensor */
	MicroMag3 _mag;

	/** \brief	The fillter for the raw data */
	MovingAverage<double, C_YAW_WINDOW_AVE_WIDTH> _yawBuffer;

	/** \brief	The message router */
	HornetManager *_hornetManager;

	/** \brief	The message buffer for Yaw data */
	CircularBuffer<MessageBuffer<1, MB_YAW>, C_MB_YAW_SIZE> _yawSender;

	/** \brief	The message buffer for raw mag data */
	CircularBuffer<MessageBuffer<3, MB_RAW_MAG>, C_MB_MAG_SIZE> _rawSender;
};

#else

class Magnetometer : public Runnable
{
public:
	Magnetometer(HornetManager* theHornetManager,SPIManager *theSPIManager, Error *e);
	bool start(){return true;}
	void run(){}
};

#endif
