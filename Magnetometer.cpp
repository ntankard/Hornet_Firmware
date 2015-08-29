#include "Magnetometer.h"

#if ENABLE_MAG == ENABLED

Magnetometer::Magnetometer(HornetManager* theHornetManager, SPIManager *theSPIManager, Error *e) :_mag(theSPIManager, e), _yawBuffer(e), _yawSender(e), _rawSender(e)
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

		double m = sqrt(pow(mag[0], 2) + pow(mag[1], 2) + pow(mag[2], 2));
		double yaw = (double)(asin(mag[0] / m));

		double addedYaw = _yawBuffer.add(yaw);

		_hornetManager->ND_RawMag(mag);
		_hornetManager->ND_Yaw(addedYaw);
	}
}

#endif
