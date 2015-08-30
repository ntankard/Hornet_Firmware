#include "Magnetometer.h"

#if ENABLE_MAG == ENABLED

#include "MessageBuffer_Passer.h"

Magnetometer::Magnetometer(HornetManager* theHornetManager, SPIManager *theSPIManager, Error *e) :_mag(theSPIManager, e), _yawBuffer(e)
{
	_hornetManager = theHornetManager;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Magnetometer::start()
{
	return _mag.init();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Magnetometer::run()
{
	int16_t mag[3];
	

	if (_mag.update())
	{
		_mag.getData(mag);

		// precces the data
		float m = sqrt(pow(mag[0], 2) + pow(mag[1], 2) + pow(mag[2], 2));
		float yaw = (float)(asin(mag[0] / m));
		float addedYaw = _yawBuffer.add(yaw);

		// Package the data
		MessageBuffer_Passer* yawMB = _yawSender.getAvailable();
		yawMB->setData(&addedYaw);
		MessageBuffer_Passer* rawMB = _rawSender.getAvailable();
		rawMB->getData()[0] = mag[0];
		rawMB->getData()[1] = mag[1];
		rawMB->getData()[2] = mag[2];

		// Send the data
		_hornetManager->newData(yawMB);
		_hornetManager->newData(rawMB);
	}
}

#endif
