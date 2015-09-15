#include "Magnetometer.h"

#ifdef USE_MAG

#include "MessageBuffer_Passer.h"

Magnetometer::Magnetometer(volatile Error *e) :_mag(e), _yawBuffer(e)
{

}

//-----------------------------------------------------------------------------------------------------------------------------

bool Magnetometer::start()
{
	return _mag.init();
}

//-----------------------------------------------------------------------------------------------------------------------------

int Magnetometer::run()
{
	int16_t mag[3];
	
	if (_mag.update())
	{
		_mag.getData(mag);

		// precces the data
		float m = sqrt(pow(mag[0], 2) + pow(mag[1], 2));

		float yaw = (float)(acos(mag[0] / m));
		float addedYaw = _yawBuffer.add(yaw);


		/*
		
		float x = (float)(asin(mag[0] / m));
		float y = (float)(asin(mag[1] / m));

		float yaw = (float)(atan(((float)mag[0]) / ((float)mag[1])));
		float addedYaw = _yawBuffer.add(yaw);
		*/


		// Package the data
		volatile MessageBuffer_Passer* yawMB = _yawSender.getAvailable();
		yawMB->getData()[0] = (addedYaw * 10000);

		volatile MessageBuffer_Passer* rawMB = _rawSender.getAvailable();
		rawMB->getData()[0] = mag[0];
		rawMB->getData()[1] = mag[1];
		rawMB->getData()[2] = mag[2];

		// Send the data
		_sendCount = 0;
		_toSend[0] = yawMB;
		_toSend[1] = rawMB;
		return 2;
	}

	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

volatile MessageBuffer_Passer* Magnetometer::getMessage() volatile
{
	_sendCount++;
	return _toSend[_sendCount - 1];
}

#endif
