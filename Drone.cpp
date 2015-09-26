#include "Drone.h"
#include "CONFIG.h"


Drone::Drone()
{
	_roll = 0;
	_pitch = 0;
	_yaw = 0;
	_throttle = 0;

	//_engines[0].attach(C_ENGINE_FRONT_LEFT);
	//_engines[1].attach(C_ENGINE_FRONT_RIGHT);
	//_engines[2].attach(C_ENGINE_REAR_RIGHT);
	//_engines[3].attach(C_ENGINE_REAR_LEFT);

	for (int i = 0; i < 4; i++)
	{
		_enginePower[i] = 0;
	}

	_isOn = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Drone::arm()
{
	_roll = 0;
	_pitch = 0;
	_yaw = 0;
	_throttle = 0;

	for (int i = 0; i < 4; i++)
	{
		_engines[i].on();
	}

	_isOn = true;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Drone::disarm()
{
	_roll = 0;
	_pitch = 0;
	_yaw = 0;
	_throttle = 0;

	for (int i = 0; i < 4; i++)
	{
		_engines[i].off();
	}

	_isOn = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Drone::isArmed()
{
	return _isOn;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Drone::setEngines(int offset)
{
	int _max = 0;
	int _min ;

	if (_throttle == 0 || !_isOn)
	{
		for (int i = 0; i < 4; i++)
		{
			_enginePower[i] = 0;
		}
	}
	else
	{
		// caculate ideal power settings
		_enginePower[0] = (_throttle - offset) +(-_pitch + _roll - _yaw)/4;
		_enginePower[1] = (_throttle - offset) +(-_pitch - _roll + _yaw)/4;
		_enginePower[2] = (_throttle - offset) + (_pitch - _roll - _yaw)/4;
		_enginePower[3] = (_throttle - offset) +( _pitch + _roll + _yaw)/4;

		_min = _enginePower[0];
		_max = _enginePower[0];

		// check to see if the power overflows
		for (int i = 1; i < 4; i++)
		{
			if (_enginePower[i] > _max)
			{
				_max = _enginePower[i];
			}
			else if (_enginePower[i] < _min)
			{
				_min = _enginePower[i];
			}
		}

		// check to see if the throttle can be adjusted to hit the target (if not fillter as neede)
		if (_max > 100 && _min != 0 && _min < 0 && _max != 100)
		{
			for (int i = 0; i < 4; i++)
			{
				if (_enginePower[i]>100)
				{
					_enginePower[i] = 100;
				}
				if (_enginePower[i] < 0)
				{
					_enginePower[i] = 0;
				}
			}
		}
		else if (_max > 100 && _min != 0)
		{
			// recaulate with a better ofset
			setEngines(_max - 100);
			return;
		}
		else if (_min < 0 && _max != 100)
		{
			// recaulate with a better ofset
			setEngines(_min);
			return;
		}
	}

	// set the motors
	for (int i = 0; i < 4; i++)
	{
		_engines[i].setPower(_enginePower[i]);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

volatile MessageBuffer_Passer* Drone::newThrottle(int t)
{
	_throttle = t;
	setEngines();
	volatile MessageBuffer_Passer* toSend = _motorSender.getAvailable();
	for (int i = 0; i < 4; i++)
	{
		toSend->getData()[i] = _enginePower[i];
	}
	return toSend;
}

//-----------------------------------------------------------------------------------------------------------------------------

volatile MessageBuffer_Passer* Drone::newPitchRoll(int p, int r)
{
	_pitch = p;
	_roll = r;
	setEngines();
	volatile MessageBuffer_Passer* toSend = _motorSender.getAvailable();
	for (int i = 0; i < 4; i++)
	{
		toSend->getData()[i] = _enginePower[i];
	}
	return toSend;
}

//-----------------------------------------------------------------------------------------------------------------------------

volatile MessageBuffer_Passer* Drone::newYaw(int y)
{
	_yaw = y;
	setEngines();
	volatile MessageBuffer_Passer* toSend = _motorSender.getAvailable();
	for (int i = 0; i < 4; i++)
	{
		toSend->getData()[i] = _enginePower[i];
	}
	return toSend;
}

//-----------------------------------------------------------------------------------------------------------------------------

volatile MessageBuffer_Passer* Drone::getCurrent()
{
	setEngines();
	volatile MessageBuffer_Passer* toSend = _motorSender.getAvailable();
	for (int i = 0; i < 4; i++)
	{
		toSend->getData()[i] = _enginePower[i];
	}
	return toSend;
}