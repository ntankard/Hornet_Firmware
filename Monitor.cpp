#include "Monitor.h"
#include "CONFIG.h"

Monitor::Monitor(ComsEncoder* theComsEncoder)
{
	_comsEncoder = theComsEncoder;
	_accRate = C_LOGGER_ACC_RATE;
	_accCount = 0;
	_isOn = false;
}

void Monitor::on()
{
	_isOn = true;
}

void Monitor::off()
{
	_isOn = false;
}

void Monitor::newAccGyro(float accel[3], float gyro[3])
{
	if (_isOn)
	{
		_accCount++;
		if (_accCount > _accRate)
		{
			_accCount = 0;
			_comsEncoder->sendAccGyro(accel, gyro);
		}
	}
}