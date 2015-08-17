#pragma once
#include <Servo.h>
#include "Arduino.h"

#include "CONFIG.h"
#include "APM_2_5_PINS.h"

#define C_MOTOR_FRONT_LEFT	PWM_1
#define C_MOTOR_FRONT_RIGHT PWM_2
#define C_MOTOR_BACK_RIGHT	PWM_3
#define C_MOTOR_BACK_LEFT	PWM_4

#define IDLE 60

class Drone
{
public:
	Drone();

	void start();

	void arm();

	void disarm();

	~Drone();
private:
	Servo _frontLeft;
	Servo _frontRight;
	Servo _backLeft;
	Servo _backRight;

	bool _isArmed;

};

