#include "AccGyro.h"

//#if ENABLE_ACC == ENABLED

#include "SPI.h"
#include "Arduino.h"


AccGyro::AccGyro(volatile Error* e) :_ins(e), _pitchBuffer(e), _rollBuffer(e)
{
	_e = e;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool AccGyro::start()
{
	return _ins.init();
}

//-----------------------------------------------------------------------------------------------------------------------------

int AccGyro::run()
{
	int16_t accel[3];
	int16_t gyro[3];

	if (_ins.update())
	{
		_ins.get_gyros(gyro);
		_ins.get_accels(accel);

		// precces the data
		/*double g = sqrt(pow(accel[0], 2) + pow(accel[1], 2) + pow(accel[2], 2));
		float roll = (float)(asin(accel[0] / g));
		float pitch = (float)((asin(accel[1] / g)));
		float addedPitch = _pitchBuffer.add(pitch);
		float addedRoll = _rollBuffer.add(roll);*/

		// Package the data
		volatile MessageBuffer_Passer* rollPitchMB = _rollPitchSender.getAvailable();
		//rollPitchMB->getData()[0] = addedPitch;
		//rollPitchMB->getData()[1] = addedRoll;

		volatile MessageBuffer_Passer* rawMB = _rawSender.getAvailable();
		rawMB->getData()[0] = accel[0];
		rawMB->getData()[1] = accel[1];
		rawMB->getData()[2] = accel[2];
		rawMB->getData()[3] = gyro[0];
		rawMB->getData()[4] = gyro[1];
		rawMB->getData()[5] = gyro[2];

		// Send the data
		_sendCount = 0;
		_toSend[0] = rollPitchMB;
		_toSend[1] = rawMB;
		return 2;
	}
}

volatile  MessageBuffer_Passer* AccGyro::getMessage() volatile
{
	_sendCount++;
	return _toSend[_sendCount - 1];
}

//#endif


