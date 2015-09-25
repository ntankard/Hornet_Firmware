#include "Stabilizer.h"

Stabilizer::Stabilizer()// :_PIDRoll(&_currentRoll, &_outRoll, &_targetRoll, 4.0, 0.2, 1.0, DIRECT) , _PIDPitch(&_currentPitch, &_outPitch, &_targetPitch, 4.0, 0.2, 1.0, DIRECT) , _PIDYaw(&_currentYaw, &_outYaw, &_targetYaw, 4.0, 0.2, 1.0, DIRECT)
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

	targetRoll = 0;
	targetPitch = 0;
	targetYaw = 0;
	 
	/*_PIDRoll.SetMode(AUTOMATIC);
	_PIDRoll.SetOutputLimits(-50, 50);
	_PIDPitch.SetMode(AUTOMATIC);
	_PIDPitch.SetOutputLimits(-50, 50);
	_PIDYaw.SetMode(AUTOMATIC);
	_PIDYaw.SetOutputLimits(-50, 50);*/
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
	//_PIDRoll.Compute();
	//_PIDPitch.Compute();
	//_PIDYaw.Compute();



	int16_t deltaRoll = targetRoll - currentRoll;
	int16_t deltaPitch = targetPitch - currentPitch;
	int16_t deltaYaw = targetYaw - currentYaw;


	//TP("TARGET :" + (String)targetRoll + "  CURRENT :" + (String)currentRoll);

	//TP((String)deltaRoll);

	int16_t settingRoll = deltaRoll / 300;
	int16_t settingPitch = deltaPitch / 600;
	int16_t settingYaw = deltaYaw / 300;

	_theDrone.newPitchRoll(-settingPitch, settingRoll);
	_theDrone.newYaw(-settingYaw);

}

volatile MessageBuffer_Passer* Stabilizer::getCurrent()
{
	return _theDrone.getCurrent();
}