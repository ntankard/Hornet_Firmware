#pragma once
#include "Error.h"
#include "Scheduler.h"
#include "DM_Indicator.h"
#include "Serial_Coms.h"
#include "ComsEncoder.h"
#include "AccGyro.h"
//#include "I2CManager.h"

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

	void changeState(State newState, int indicatorPriority, int comEncoderPri, int accGyroPri, int lightSetting, int lightBlinks, int lightRate);

	State _state;
	unsigned long _C_last;


	Scheduler _scheduler;
	volatile Error _e;

	// all other objects
	Indicator _indicator;
	ComsEncoder _comsEncoder;
	AccGyro _accGyro;
	//I2CManager _I2CManager;
	
};

