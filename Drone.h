#pragma once
#include <Servo.h>
#include "Arduino.h"

#include "CONFIG.h"
#include "APM_2_5_PINS.h"

#define C_MOTOR_FRONT_LEFT	PWM_3
#define C_MOTOR_FRONT_RIGHT PWM_4
#define C_MOTOR_BACK_RIGHT	PWM_5
#define C_MOTOR_BACK_LEFT	PWM_6

#define IDLE 60
#define MAX 135

class Drone
{
public:
	Drone();

	void start();

	void arm();

	void disarm();

	void setThrottle(int p);

	~Drone();
private:
	Servo _frontLeft;
	Servo _frontRight;
	Servo _backLeft;
	Servo _backRight;

	bool _isArmed;

};

