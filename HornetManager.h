#pragma once
#include "Error.h"
#include "Scheduler.h"
#include "DM_Indicator.h"
#include "Serial_Coms.h"
#include "ComsEncoder.h"

enum State{ Init, Connect, Idle ,TakeOff,Flight,Land,Emergency,Crash};


class HornetManager
{
public:

	HornetManager();
	void start();
	void run();

	void newMessage(uint8_t data);
	void newData(MessageBuffer_Passer* data);

private:

	void runConnect();

	void changeState(State newState, int indicatorPriority,int comEncoderPri, int lightSetting, int lightBlinks, int lightRate);

	State _state;
	unsigned long _C_last;


	Scheduler _scheduler;
	volatile Error _e;

	// all other objects
	Indicator _indicator;
	//Coms _coms;
	ComsEncoder _comsEncoder;
	
};

