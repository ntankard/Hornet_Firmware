#pragma once
#include "Error.h"
#include "Scheduler.h"

enum State{ Init, Connect, Idle ,TakeOff,Flight,Land,Emergency,Crash};


class HornetManager
{
public:

	HornetManager(Error *theError);
	void start();
	void run();

private:

	void changeState(State newState);

	State _state;
	Scheduler _scheduler;
	Error *_e;
};

