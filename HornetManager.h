#pragma once
#include "Error.h"
#include "Scheduler.h"
#include "DM_Indicator.h"
#include "Serial_Coms.h"
#include "ComsEncoder.h"
#include "Gyro.h"

enum State{ Init, Connect, Idle ,TakeOff,Flight,Land,Emergency,Crash};


class HornetManager
{
public:

	HornetManager();
	void start();
	void run();

	void newMessage(uint8_t data);
	void newData(volatile MessageBuffer_Passer* data);

private:

	void runConnect();

	void changeState(State newState, int indicatorPriority, int comEncoderPri, int gyroPri, int lightSetting, int lightBlinks, int lightRate);

	State _state;
	unsigned long _C_last;


	Scheduler _scheduler;
	volatile Error _e;

	// all other objects
	Indicator _indicator;
	ComsEncoder _comsEncoder;
	Gyro _gyro;
	
};

