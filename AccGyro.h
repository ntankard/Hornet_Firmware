#pragma once
#include "HornetManager.h"
#include "AP_InertialSensor_MPU6000.h"
#include "Error.h"

class AccGyro
{
public:
	AccGyro(HornetManager* theManager);

	void start();

	void run();

private:
	HornetManager* _hornetManager;
	AP_InertialSensor_MPU6000 _ins;
};

