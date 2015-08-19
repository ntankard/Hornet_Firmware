#include "Monitor.h"
#include "CONFIG.h"

Monitor::Monitor(ComsEncoder* theComsEncoder)
{
	_comsEncoder = theComsEncoder;
	_rawAccRate = C_LOGGER_ACC_RATE;
	_rawAccCount = 0;
	_isOn = false;
	_pitchRollRate = C_LOGGER_PITCH_ROLL_RATE;
	_pitchRollCount = 0;
}

void Monitor::on()
{
	_isOn = true;
}

void Monitor::off()
{
	_isOn = false;
}

void Monitor::newRawAccGyro(float accel[3], float gyro[3])
{
	if (_isOn)
	{
		_rawAccCount++;
		if (_rawAccCount > _rawAccRate)
		{
			_rawAccCount = 0;
			_comsEncoder->sendRawAccGyro(accel, gyro);
		}
	}
}

void Monitor::newPitchRoll(float pitch, float roll)
{
	if (_isOn)
	{
		_pitchRollCount++;
		if (_pitchRollCount > _pitchRollRate)
		{
			_pitchRollCount = 0;
			_comsEncoder->sendPitchRoll(pitch, roll);
		}
	}
}