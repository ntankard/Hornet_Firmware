#pragma once
#include "CONFIG.h"
#include "Runnable.h"
#include "Error.h"

#ifdef USE_ACC

#include "Error.h"
#include "SPIManager.h"
#include "I2CManager.h"
#include <stdint.h>

#include "AP_InertialSensor_MPU6050.h"
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
	AccGyro(volatile Error* e);

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
	int run();

	volatile  MessageBuffer_Passer* getMessage()volatile;

private:

	volatile MessageBuffer_Passer* _toSend[2];

	int _sendCount;

	/** \brief	The shared error object (mimics exeptions in c++) */
	volatile Error* _e;

	/** \brief	The fillter for the raw pitch data */
	MovingAverage<float, C_PITCH_ROLL_WINDOW_AVE_WIDTH> _pitchBuffer;

	/** \brief	The fillter for the raw roll data */
	MovingAverage<float, C_PITCH_ROLL_WINDOW_AVE_WIDTH> _rollBuffer;

	/** \brief	The message buffers for rollPitch data */
	volatile MessageBuffer_Manager<MB_ROLL_PITCH_SETTINGS> _rollPitchSender;

	/** \brief	The message buffers for raw acc data */
	volatile MessageBuffer_Manager<MB_RAW_ACC_SETTINGS> _rawSender;

	/** \brief	The MPU600XX device */
	AP_InertialSensor_MPU600xx _ins;
};
#else

class AccGyro:public Runnable
{
public:
	AccGyro(volatile Error* e){}
	bool start(){return true;}
	int run(){return 0;}
	volatile  MessageBuffer_Passer* getMessage()volatile{return NULL;}
};

#endif
