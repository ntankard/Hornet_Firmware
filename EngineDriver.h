#pragma once

#include <Servo.h>

class EngineDriver
{
public:
	EngineDriver();
	void attach(int PWMPin);
	void on();
	void off();
	bool isOn();

	// range 0 to 100%
	void setPower(double p);
private:
	Servo _engine;
	bool _isOn;

};

