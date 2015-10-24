#pragma once
#include "CONFIG.h"
#include "Runnable.h"

#if ENABLE_ACC == ENABLED

#include "HornetManager.h"
#include "Error.h"
#include "SPIManager.h"
#include "I2CManager.h"
#include <stdint.h>

#include "AP_InertialSensor_MPU600xx.h"
#include "MovingAverage.h"
#include "MessageBuffer_Manager.h"

/**
* \brief	A mamanger for a MPU600xx accelerometer
*/
class AccGyro :public Runnable
{
public:

	/**
	* \brief	Constctor for the MPU6000
	*
	* \param	theHornetManager	The systems message router
	* \param	theI2CManager		THe I2C object to use to comunicate with the device
	* \param	e					The hared error object
	*/
	AccGyro(HornetManager* theManager, I2CManager *theI2CManager, Error* e);

	/**
	* \brief	Constctor for the MPU6050
	*
	* \param	theHornetManager	The systems message router
	* \param	theSPIManager		THe SPI object to use to comunicate with the device
	* \param	cs_pin				The chip select pin for SPI comunication
	* \param	e					The hared error object
	*/
	AccGyro(HornetManager* theManager, SPIManager *theSPIManager, uint8_t cs_pin, Error* e);

	/**
	* \brief	Setupt the conection to the device
	*
	* \return	Was the device conected to sucsesfuly
	*/
	bool start();

	/**
	* \brief	Exicute a step in the operation of the accelerometer
	*
	* \throw	E_HARDWARE_FAILURE	If the read times out
	*/
	void run();

private:

	/** \brief	The message router */
	HornetManager* _hornetManager;

	/** \brief	The shared error object (mimics exeptions in c++) */
	Error* _e;

	/** \brief	The fillter for the raw pitch data */
	MovingAverage<float, C_PITCH_ROLL_WINDOW_AVE_WIDTH> _pitchBuffer;

	/** \brief	The fillter for the raw roll data */
	MovingAverage<float, C_PITCH_ROLL_WINDOW_AVE_WIDTH> _rollBuffer;

	/** \brief	The message buffers for rollPitch data */
	MessageBuffer_Manager<MB_ROLL_PITCH_SETTINGS> _rollPitchSender;

	/** \brief	The message buffers for raw acc data */
	MessageBuffer_Manager<MB_RAW_ACC_SETTINGS> _rawSender;

	/** \brief	The MPU600XX device */
	AP_InertialSensor_MPU600xx _ins;
};
#else

class AccGyro:public Runnable
{
public:
	AccGyro(){}
	bool start(){ return true; }
	void run(){}
};

#endif
