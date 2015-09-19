#pragma once

#include "MessageBuffer_Manager.h"
#include "CONFIG.h"

#include "EngineDriver.h"

class Drone
{
public:
	Drone();

	void arm();
	void disarm();
	bool isArmed();

	volatile MessageBuffer_Passer* newThrottle(int t);
	volatile MessageBuffer_Passer* newPitchRoll(int p, int r);
	volatile MessageBuffer_Passer* newYaw(int y);

	volatile MessageBuffer_Passer* getCurrent();
private:

	void setEngines(int offset =0);

	int _roll;
	int _pitch;
	int _yaw;
	int _throttle;

	bool _isOn;

	int _enginePower[4];
	EngineDriver _engines[4];

	MessageBuffer_Manager<MB_MOTOR_SETTING> _motorSender;
};

