#pragma once
#include "Stabilizer.h"

class FlightController
{
public:
	FlightController();
	void arm();
	void disarm();

	void newGyro(volatile MessageBuffer_Passer *gyro);

	void newJoyXY(volatile MessageBuffer_Passer *XY);

	void newJoyThrottle(volatile MessageBuffer_Passer *throttle);

	volatile MessageBuffer_Passer* getCurrent();

private:
	Stabilizer _theStabilizer;
	uint16_t _lastYaw;

	bool _isArmed;

};

