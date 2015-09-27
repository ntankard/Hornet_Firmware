#pragma once
#include "Stabilizer.h"
#include "Runnable.h"
#include "MessageBuffer.h"
#include "TimeOut.h"
#include <Servo.h>

class FlightController : public Runnable
{
public:
	FlightController();

	bool start();

	int run();

	volatile MessageBuffer_Passer* getMessage()volatile { return &_empty; }


	void arm();
	void disarm();

	void newGyro(volatile MessageBuffer_Passer *gyro);

	void newJoyXY(volatile MessageBuffer_Passer *XY);

	void newJoyZ(volatile MessageBuffer_Passer *Z);

	void newJoyThrottle(volatile MessageBuffer_Passer *throttle);


private:
	//Stabilizer _theStabilizer;
	//uint16_t _lastYaw;

	bool _isArmed;
	bool _isArmingDisArming;
	bool _isArming;
	TimeOut _armTime;

	volatile MessageBuffer<0,0,1> _empty;

	Servo _roll;
	Servo _pitch;
	Servo _yaw;
	Servo _throttle;

};

