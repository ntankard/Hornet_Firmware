#include "Magnetometer.h"

#if ENABLE_MAG == ENABLED

Magnetometer::Magnetometer(SPIManager *theSPIManager, Error *e) :_mag(theSPIManager, e)
{
}

bool Magnetometer::start()
{
	if (_mag.init())
	{
		while (true)
		{
			Serial.println("YES");
		}
	}
	else
	{
		while (true)
		{
			Serial.println("NO");
		}
	}

	return true;
}
void Magnetometer::run()
{
	_mag.update();
}

#endif
