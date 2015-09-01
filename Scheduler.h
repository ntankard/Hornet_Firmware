#pragma once
#include "Runnable.h"
#include "CONFIG.h"
#include "Error.h"

struct Pair
{
	Runnable *thread;
	int priority;
};

class Scheduler
{
public:

	Scheduler(Error *e);

	void addRunable(int ID, Runnable *theRunnable);

	bool finish();

	void setPriority(int ID, int p);

	void run();

private:
	Error *_e;
	Pair _threads[C_SCHEDULER_THREAD_NUM];
	int _setCount;
	int _runCount[C_SCHEDULER_THREAD_NUM];
	
};

