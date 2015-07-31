#pragma once
#include "ComsEncoder.h"
#include "Error.h"

class Monitor
{
public:
	Monitor(ComsEncoder* theComsEncoder, Error *e);

	void on();

	void off();

	void newAccGyro(float accel[3], float gyro[3]);

private:
	ComsEncoder *_comsEncoder;
	Error *_e;

	int _accRate;
	int _accCount;
	bool _isOn;
};

