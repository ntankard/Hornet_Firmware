#include "Stabilizer.h"

Stabilizer::Stabilizer()
{
	currentRoll = 0;
	currentPitch = 0;
	currentYaw = 0;

	targetRoll = 0;
	targetPitch = 0;
	targetYaw = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Stabilizer::arm()
{
	_theDrone.arm();
	currentRoll = 0;
	currentPitch = 0;
	currentYaw = 0;

	targetRoll = 0;
	targetPitch = 0;
	targetYaw = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Stabilizer::disarm()
{
	_theDrone.disarm();
	currentRoll = 0;
	currentPitch = 0;
	currentYaw = 0;

	targetRoll = 0;
	targetPitch = 0;
	targetYaw = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Stabilizer::newGyro(volatile MessageBuffer_Passer *gyro)
{
	currentRoll = gyro->getData()[0];
	currentPitch = gyro->getData()[1];
	currentYaw = gyro->getData()[2];
	caculateDronePos();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Stabilizer::newTargetPos(int16_t r, int16_t p)
{
	targetRoll = r;
	targetPitch = p;
	caculateDronePos();
}

void Stabilizer::newYaw(int16_t y)
{
	targetYaw = y;
	caculateDronePos();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Stabilizer::newThrottle(int16_t t)
{
	_theDrone.newThrottle(t);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Stabilizer::caculateDronePos()
{
	int16_t deltaRoll = targetRoll - currentRoll;
	int16_t deltaPitch = targetPitch - currentPitch;
	int16_t deltaYaw = targetYaw - currentYaw;


	//TP("TARGET :" + (String)targetRoll + "  CURRENT :" + (String)currentRoll);

	TP((String)deltaRoll);

	int16_t settingRoll = deltaRoll / 100;
	int16_t settingPitch = deltaPitch / 100;
	int16_t settingYaw = deltaYaw / 100;

	_theDrone.newPitchRoll(settingPitch, settingRoll);
	_theDrone.newYaw(settingYaw);

}

volatile MessageBuffer_Passer* Stabilizer::getCurrent()
{
	return _theDrone.getCurrent();
}