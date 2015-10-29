#include "FlightController.h"

#include "CONFIG.h"

#define MIN 1000
#define MAX 2000
#define MULTIPLYER 10


FlightController::FlightController()
{
	_state = Disarmed;

	_roll.attach(C_APM_ROLL);
	_pitch.attach(C_APM_PITCH);
	_throttle.attach(C_APM_THROTTLE);
	_yaw.attach(C_APM_YAW);

	_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_throttle.writeMicroseconds(MIN);

	_TotalVector.getData()[0] = 50;
	_TotalVector.getData()[1] = 50;
	_JoyVector.getData()[0] = 50;
	_JoyVector.getData()[1] = 50;

	_regReadCount = 0;
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
	case MB_COMPENSATOR_VECTOR:
		_CompensationVector = newRegister;
		break;
	case MB_AVOID:
		_AvoidRegister = newRegister;
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
	// check for state transitions
	switch (_state)
	{
	case Arming:
		if (_armTime.hasTimeOut())
		{
			_state = Armed;

			_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_throttle.writeMicroseconds(MIN);
		}
		break;
	case Disarming:
		if (_armTime.hasTimeOut())
		{
			_state = Disarmed;

			_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_throttle.writeMicroseconds(MIN);
		}
		break;
	}
	
	switch (_state)
	{
	case Disarmed:
		if (_ArmDisarmRegister->getData()[0] != 0)
		{
			arm();
		}
		break;
	case Armed:
		if (_ArmDisarmRegister->getData()[0] == 0)
		{
			disarm();
		}
		break;
	}
	

	// update joystick values
	if (_state == Armed)
	{
		_JoyVector.getData()[0] = _XYJoyRegister->getData()[0];
		_JoyVector.getData()[1] = _XYJoyRegister->getData()[1];

		int roll;
		int pitch;

		if (_AvoidRegister->getData()[0] == 0)
		{
			roll = _XYJoyRegister->getData()[0];
			pitch = _XYJoyRegister->getData()[1];
		}
		else
		{
			roll = (((_XYJoyRegister->getData()[0]-50)*2) + ((_CompensationVector->getData()[0]-50)*2))/2 +50;
			pitch = (((_XYJoyRegister->getData()[1] - 50) * 2) + ((_CompensationVector->getData()[1] - 50) * 2))/2+50;
		}

		_roll.writeMicroseconds(roll* MULTIPLYER + MIN);
		_pitch.writeMicroseconds(pitch* MULTIPLYER + MIN);
		_yaw.writeMicroseconds(_ZJoyRegister->getData()[0] * MULTIPLYER + MIN);
		_throttle.writeMicroseconds(_throttleJoyRegister->getData()[0] * MULTIPLYER + MIN);

		_TotalVector.getData()[0] = roll;
		_TotalVector.getData()[1] = pitch;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::arm()
{
	if (_state == Disarmed)
	{
		// start arm
		_armTime.start(5000);
		_state = Arming;

		_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_yaw.writeMicroseconds(MAX);
		_throttle.writeMicroseconds(MIN);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::disarm()
{
	if (_state == Armed)
	{
		// start disarm
		_armTime.start(3000);
		_state = Disarming;

		_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_yaw.writeMicroseconds(MIN);
		_throttle.writeMicroseconds(MIN);

		_TotalVector.getData()[0] = 50;
		_TotalVector.getData()[1] = 50;
		_JoyVector.getData()[0] = 50;
		_JoyVector.getData()[1] = 50;
	}
}