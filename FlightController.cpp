#include "FlightController.h"


FlightController::FlightController()
{
	_isArmed = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::arm()
{
	_theStabilizer.arm();
	_isArmed = true;
	_theStabilizer.newYaw(_lastYaw);
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::disarm()
{
	_theStabilizer.disarm();
	_isArmed = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::newGyro(volatile MessageBuffer_Passer *gyro)
{
	if (!_isArmed)
	{
		_lastYaw = gyro->getData()[2];
	}
	else
	{
		_theStabilizer.newGyro(gyro);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::newJoyXY(volatile MessageBuffer_Passer *XY)
{
	int16_t MAX_ANGLE = 40;

	_theStabilizer.newTargetPos(MAX_ANGLE * XY->getData()[0], MAX_ANGLE * XY->getData()[1]);
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::newJoyThrottle(volatile MessageBuffer_Passer *throttle)
{
	_theStabilizer.newThrottle(throttle->getData()[0]);
}

volatile MessageBuffer_Passer* FlightController::getCurrent()
{
	return _theStabilizer.getCurrent();
}