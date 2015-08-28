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
	//Scheduler(Coms* theComs, ComsEncoder* theComsEncoder, AccGyro* theAccGyro, Indicator* theIndicator, Lidar* theLidar);
	Scheduler(Error *e);

	void addRunable(int ID, Runnable *theRunnable);

	bool finish();

	void setPriority(int ID, int p);

//	void setAccPriority(int p);

	//void setIndicatorPriority(int p);

	//void setLidarPriority(int p);

	void run();

private:
	Error *_e;
	Pair _threads[C_SCHEDULER_THREAD_NUM];
	int _setCount;
	int _runCount[C_SCHEDULER_THREAD_NUM];
	

	/*Coms* _coms;
	ComsEncoder* _comsEncoder;

	int _accPriority;
	int _accRunCount;
	AccGyro* _accGyro;

	int _indicatorPriority;
	int _indicatorRunCount;
	Indicator* _indicator;

	int _lidarPriority;
	int _lidarRunCount;
	Lidar* _lidar;*/
};

