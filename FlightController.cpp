#include "FlightController.h"

#include "CONFIG.h"

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

void FlightController::addRegister(volatile MessageBuffer_Passer* newRegister)
{
	switch (newRegister->getID())
	{
	case MB_JOY_XY:
		_XYJoyRegister = newRegister;
		break;
	case MB_JOY_THROTTLE:
		_throttleJoyRegister = newRegister;
		break;
	case MB_JOY_Z:
		_ZJoyRegister = newRegister;
		break;
	case MB_ARM_DISARM:
		_ArmDisarmRegister = newRegister;
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

bool FlightController::start()
{
	disarm();
	if (_XYJoyRegister->getID() != MB_JOY_XY ||
		_throttleJoyRegister->getID() != MB_JOY_THROTTLE ||
		_ZJoyRegister->getID() != MB_JOY_Z ||
		_ArmDisarmRegister->getID() != MB_ARM_DISARM)
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool FlightController::run()
{
	// check ongoing arm/disarm
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


	// check for new arm/disarm
	if (!_isArmingDisArming)
	{
		// check for new arm/disarm
		if (_ArmDisarmRegister->getData()[0] != _isArmed)
		{
			if (_isArmed)
			{
				disarm();
			}
			else
			{
				arm();
			}
		}
	}

	// update joystick values
	if (!_isArmingDisArming)
	{
		_roll.writeMicroseconds(_XYJoyRegister->getData()[0] * MULTIPLYER + MIN);
		_pitch.writeMicroseconds(_XYJoyRegister->getData()[1] * MULTIPLYER + MIN);
		_yaw.writeMicroseconds(_ZJoyRegister->getData()[0] * MULTIPLYER + MIN);
		_throttle.writeMicroseconds(_throttleJoyRegister->getData()[0] * MULTIPLYER + MIN);
	}

	return false;
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