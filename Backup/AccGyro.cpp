#include "AccGyro.h"

#if ENABLE_ACC == ENABLED

#include "SPI.h"
#include "Arduino.h"


AccGyro::AccGyro(HornetManager* theManager, I2CManager *theI2CManager, Error* e) :_ins(e, theI2CManager), _pitchBuffer(e), _rollBuffer(e)
{
	_hornetManager = theManager;
	_e = e;
}

//-----------------------------------------------------------------------------------------------------------------------------

AccGyro::AccGyro(HornetManager* theManager, SPIManager *theSPIManager, uint8_t cs_pin, Error* e) : _ins(e, theSPIManager, cs_pin), _pitchBuffer(e), _rollBuffer(e)
{
	_hornetManager = theManager;
	_e = e;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool AccGyro::start()
{
	return _ins.init();
}

//-----------------------------------------------------------------------------------------------------------------------------

void AccGyro::run()
{
	float accel[3];
	float gyro[3];

	if (_ins.update())
	{
		_ins.get_gyros(gyro);
		_ins.get_accels(accel);

		// precces the data
		double g = sqrt(pow(accel[0], 2) + pow(accel[1], 2) + pow(accel[2], 2));
		float roll = (float)(asin(accel[0] / g));
		float pitch = (float)((asin(accel[1] / g)));
		float addedPitch = _pitchBuffer.add(pitch);
		float addedRoll = _rollBuffer.add(roll);

		// Package the data
		MessageBuffer_Passer* rollPitchMB = _rollPitchSender.getAvailable();
		rollPitchMB->getData()[0] = addedPitch;
		rollPitchMB->getData()[1] = addedRoll;

		MessageBuffer_Passer* rawMB = _rawSender.getAvailable();
		rawMB->getData()[0] = accel[0];
		rawMB->getData()[1] = accel[1];
		rawMB->getData()[2] = accel[2];
		rawMB->getData()[3] = gyro[0];
		rawMB->getData()[4] = gyro[1];
		rawMB->getData()[5] = gyro[2];

		// Send the data
		_hornetManager->newData(rollPitchMB);
		_hornetManager->newData(rawMB);
	}
}

#endif


