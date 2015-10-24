#pragma once
#include "Error.h"
#include "Scheduler.h"
#include "Indicator.h"
#include "ComsEncoder.h"
#include "Gyro.h"
#include "FlightController.h"
#include "Lidar.h"

enum State{ Init = 0, Connect = 1, Idle =2,TakeOff=3,Flight=4,Land=5,Emergency=6,Crash=7};

class HornetManager
{
public:

	HornetManager();
	void start();
	void run();

private:

	void changeState(State newState, int indicatorPriority, int comEncoderPri, int gyroPri, int flightPri, int lidarPri, int lightSetting, int lightBlinks, int lightRate);

	State _state;

	// core objects
	Scheduler _scheduler;
	volatile Error _e;

	// all other objects
	Indicator _indicator;
	ComsEncoder _comsEncoder;
	Gyro _gyro;
	FlightController _theDrone;
	Lidar _LIDAR;

	// status monitor
	int _loopCount;
	unsigned long _statusLast;
	MessageBuffer<MB_STATUS, 2> _statusRegister;
};

