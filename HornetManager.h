#pragma once
#include "Error.h"
#include "Scheduler.h"
#include "DM_Indicator.h"

enum State{ Init, Connect, Idle ,TakeOff,Flight,Land,Emergency,Crash};


class HornetManager
{
public:

	HornetManager(Error *theError);
	void start();
	void run();

private:

	void changeState(State newState, int indicatorPriority, int lightSetting, int lightBlinks, int lightRate);

	State _state;
	Scheduler _scheduler;
	Error *_e;
	Indicator _indicator;
};

