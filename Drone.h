#pragma once

#include "MessageBuffer_Manager.h"
#include "CONFIG.h"
class Drone
{
public:
	Drone();

	volatile MessageBuffer_Passer* newThrottle(int t);
	volatile MessageBuffer_Passer* newPitchRoll(int p, int r);
	volatile MessageBuffer_Passer* newYaw(int y);

	volatile MessageBuffer_Passer* getCurrent();
private:

	void caculateMotor();

	int _roll;
	int _pitch;
	int _yaw;
	int _throttle;

	int _motorPower[4];

	MessageBuffer_Manager<MB_MOTOR_SETTING> _motorSender;
};

