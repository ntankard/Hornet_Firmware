#include "Drone.h"
#include "CONFIG.h"


Drone::Drone()
{
	_roll = 0;
	_pitch = 0;
	_yaw = 0;
	_throttle = 0;
}

void Drone::caculateMotor()
{
	if (_throttle == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			_motorPower[i] = 0;
		}
	}
	else
	{
		_motorPower[0] = _throttle - _pitch - _roll + _yaw;
		_motorPower[1] = _throttle - _pitch + _roll - _yaw;
		_motorPower[2] = _throttle + _pitch + _roll + _yaw;
		_motorPower[3] = _throttle + _pitch - _roll - _yaw;


		for (int i = 0; i < 4; i++)
		{
			if (_motorPower[i]>100)
			{
				_motorPower[i] = 100;
			}
			if (_motorPower[i] < 0)
			{
				_motorPower[i] = 0;
			}
		}
	}
}

volatile MessageBuffer_Passer* Drone::newThrottle(int t)
{
	_throttle = t;
	caculateMotor();
	volatile MessageBuffer_Passer* toSend = _motorSender.getAvailable();
	for (int i = 0; i < 4; i++)
	{
		toSend->getData()[i] = _motorPower[i];
	}
	return toSend;
}
volatile MessageBuffer_Passer* Drone::newPitchRoll(int p, int r)
{
	_pitch = p-50;
	_roll = r-50;
	caculateMotor();
	volatile MessageBuffer_Passer* toSend = _motorSender.getAvailable();
	for (int i = 0; i < 4; i++)
	{
		toSend->getData()[i] = _motorPower[i];
	}
	return toSend;
}
volatile MessageBuffer_Passer* Drone::newYaw(int y)
{
	_yaw = y-50;
	caculateMotor();
	volatile MessageBuffer_Passer* toSend = _motorSender.getAvailable();
	for (int i = 0; i < 4; i++)
	{
		toSend->getData()[i] = _motorPower[i];
	}
	return toSend;
}

volatile MessageBuffer_Passer* Drone::getCurrent()
{
	caculateMotor();
	volatile MessageBuffer_Passer* toSend = _motorSender.getAvailable();
	for (int i = 0; i < 4; i++)
	{
		toSend->getData()[i] = _motorPower[i];
	}
	return toSend;
}