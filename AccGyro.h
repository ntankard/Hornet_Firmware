#pragma once
#include "HornetManager.h"
#include "AP_InertialSensor_MPU6000.h"
#include "Error.h"
#include "CircularBuffer.h"

class AccGyro
{
public:
	AccGyro(HornetManager* theManager);

	void start();

	void run();

private:
	HornetManager* _hornetManager;
	//CircularBuffer<int,5> _rollBuffer;

#ifdef USE_ACC
	AP_InertialSensor_MPU6000 _ins;
#endif
};

