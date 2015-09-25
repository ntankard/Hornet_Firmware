#pragma once

#include "Drone.h"
#include "MessageBuffer_Passer.h"
//#include "PID_v1.h"

class Stabilizer
{
public:
	Stabilizer();

	void arm();
	void disarm();

	void newGyro(volatile MessageBuffer_Passer *gyro);

	void newTargetPos(int16_t r, int16_t p);
	void newYaw(int16_t y);
	void newThrottle(int16_t t);

	volatile MessageBuffer_Passer* getCurrent();

private:

	void caculateDronePos();

	int16_t currentRoll;
	int16_t currentPitch;
	int16_t currentYaw;

	int16_t targetRoll;
	int16_t targetPitch;
	int16_t targetYaw;

	//PID _PIDRoll;
	//PID _PIDPitch;
	//PID _PIDYaw;

	double _targetRoll;
	double _currentRoll;
	double _outRoll;

	double _targetPitch;
	double _currentPitch;
	double _outPitch;

	double _targetYaw;
	double _currentYaw;
	double _outYaw;




	Drone _theDrone;

};

