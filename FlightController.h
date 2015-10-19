#pragma once

#include "Runnable.h"
#include "MessageBuffer.h"
#include "TimeOut.h"
#include <Servo.h>

class FlightController : public Runnable
{
public:
	FlightController();

	int getNORegisters(){ return 0; }
	volatile MessageBuffer_Passer* getRegister(){ return &_empty; }
	void addRegister(volatile MessageBuffer_Passer* newRegister);

	bool start();

	bool run();

private:
	MessageBuffer<0, 1> _empty;
	void arm();
	void disarm();

	//Stabilizer _theStabilizer;
	//uint16_t _lastYaw;

	bool _isArmed;
	bool _isArmingDisArming;
	bool _isArming;
	TimeOut _armTime;

	Servo _roll;
	Servo _pitch;
	Servo _yaw;
	Servo _throttle;

	volatile MessageBuffer_Passer* _throttleJoyRegister;
	volatile MessageBuffer_Passer* _XYJoyRegister;
	volatile MessageBuffer_Passer* _ZJoyRegister;
	volatile MessageBuffer_Passer* _ArmDisarmRegister;
};

