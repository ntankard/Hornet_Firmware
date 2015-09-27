#include "FlightController.h"

#define MIN 1000
#define MAX 2000
#define MULTIPLYER 10


FlightController::FlightController()
{
	_isArmed = false;
	_isArmingDisArming = false;
	_isArming = false;

	_roll.attach(C_APM_ROLL);
	_pitch.attach(C_APM_PITCH);
	_throttle.attach(C_APM_THROTTLE);
	_yaw.attach(C_APM_YAW);

	_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_throttle.writeMicroseconds(MIN);
}

//-----------------------------------------------------------------------------------------------------------------------------

bool FlightController::start()
{
	disarm();
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

int FlightController::run()
{
	if (_isArmingDisArming)
	{
		if (_armTime.hasTimeOut())
		{
			if (_isArming)
			{
				// end arm
				_isArmed = true;
				_isArmingDisArming = false;

				_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
				_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
				_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
				_throttle.writeMicroseconds(MIN);
			}
			else
			{
				// end disarm
				_isArmingDisArming = false;

				_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
				_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
				_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
				_throttle.writeMicroseconds(MIN);
			}
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::arm()
{
	if (!_isArmingDisArming && !_isArmed)
	{
		// start arm
		_armTime.start(5000);
		_isArming = true;
		_isArmingDisArming = true;

		_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_yaw.writeMicroseconds(MAX);
		_throttle.writeMicroseconds(MIN);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::disarm()
{
	if (!_isArmingDisArming && _isArmed)
	{
		// start disarm
		_armTime.start(3000);
		_isArmed = false;
		_isArming = false;
		_isArmingDisArming = true;

		_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_yaw.writeMicroseconds(MIN);
		_throttle.writeMicroseconds(MIN);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::newGyro(volatile MessageBuffer_Passer *gyro)
{
	
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::newJoyXY(volatile MessageBuffer_Passer *XY)
{
	if (_isArmed)
	{
		_roll.writeMicroseconds(XY->getData()[0] * MULTIPLYER + MIN);
		_pitch.writeMicroseconds(XY->getData()[1] * MULTIPLYER + MIN);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::newJoyZ(volatile MessageBuffer_Passer *Z)
{
	if (_isArmed)
	{
		_yaw.writeMicroseconds(Z->getData()[0] * MULTIPLYER + MIN);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::newJoyThrottle(volatile MessageBuffer_Passer *throttle)
{
	if (_isArmed)
	{
		_throttle.writeMicroseconds(throttle->getData()[0] * MULTIPLYER + MIN);
	}
}
