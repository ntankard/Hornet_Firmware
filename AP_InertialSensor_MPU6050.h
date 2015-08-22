#pragma once

#include "CONFIG.h"

#ifdef USE_MPU6050

class AP_InertialSensor_MPU6050
{
public:
	AP_InertialSensor_MPU6050();

	void init();
	bool update();
	void get_gyros(float *);
	void get_accels(float *);
};

#endif

