#include "AccGyro.h"

#if ENABLE_ACC == ENABLED

#include "SPI.h"
#include "Arduino.h"


AccGyro::AccGyro(HornetManager* theManager, Error* e, I2CManager *theI2CManager, uint8_t interruptPin) :_ins(theI2CManager, interruptPin), _pitchBuffer(e), _rollBuffer(e)
{
	_hornetManager = theManager;
	_e = e;
}

//-----------------------------------------------------------------------------------------------------------------------------

AccGyro::AccGyro(HornetManager* theManager, Error* e, SPIManager *theSPIManager, uint8_t cs_pin, uint8_t interruptPin) : _ins(theSPIManager, cs_pin, interruptPin), _pitchBuffer(e), _rollBuffer(e)
{
	_hornetManager = theManager;
	_e = e;
}

void AccGyro::start()
{
	_ins.init();
}

void AccGyro::run()
{
	float accel[3];
	float gyro[3];

	/*

#ifdef USE_MPU6000

	if (_ins.update()){
		_ins.get_gyros(gyro);
		_ins.get_accels(accel);

		// Calculate pitch and roll
		double g = sqrt(pow(accel[0], 2) + pow(accel[1], 2) + pow(accel[2], 2));
		float roll = (float)(asin(accel[0] / g));
		float pitch = (float)((asin(accel[1] / g)));

		_hornetManager->ND_RawAccGyro(accel, gyro);
		_hornetManager->ND_PitchRoll(_pitchBuffer.add(pitch), _rollBuffer.add(roll));
	}

#endif
#ifdef USE_MPU6050

#endif*/
}

#endif


