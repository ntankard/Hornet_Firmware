#pragma once
#include "HornetManager.h"
#include "Error.h"
#include "CONFIG.h"

#if ENABLE_ACC == ENABLED

#include "CircularBuffer.h"
#include "MovingAverage.h"
#include "AP_InertialSensor_MPU6000.h"

class AccGyro
{
public:
	AccGyro(HornetManager* theManager, Error* e);

	void start();

	void run();

private:
	HornetManager* _hornetManager;
	//CircularBuffer<int,5> _rollBuffer;
	MovingAverage<float, C_PITCH_ROLL_WINDOW_AVE_WIDTH> _pitchBuffer;
	MovingAverage<float, C_PITCH_ROLL_WINDOW_AVE_WIDTH> _rollBuffer;
	Error* _e;



	AP_InertialSensor_MPU6000 _ins;

};
#else

class AccGyro
{
public:
	AccGyro(HornetManager* theManager, Error* e){}
	void start(){}
	void run(){}
};

#endif
