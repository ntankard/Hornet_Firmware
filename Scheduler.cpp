#include "Scheduler.h"

Scheduler::Scheduler(Error *e)
{
	_e = e;
	_setCount = 0;
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		_runCount[i] = 0;
		_threads[i].thread = NULL;
		_threads[i].priority = 1;
	}
}

void Scheduler::addRunable(int ID, Runnable *theRunnable)
{
	if (theRunnable == NULL)
	{
		_e->add(E_SETUP_ERROR, "Attempting to add a null runable");
		return;
	}

	if (_threads[ID].thread != NULL)
	{
		_e->add(E_SETUP_ERROR, "Attempting to overwright a existing thread" + (String)ID);
		return;
	}

	_threads[ID].thread = theRunnable;
	_threads[ID].priority = 1;
	_setCount++;
}

bool Scheduler::finish()
{
	//Serial.print((String)_setCount);
	return !(_setCount == C_SCHEDULER_THREAD_NUM);
}

void Scheduler::setPriority(int ID, int p)
{
	_threads[ID].priority = p;
}

void Scheduler::run()
{
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		if (_threads[i].priority != 0)
		{
			_runCount[i]++;
			if (_runCount[i] >= _threads[i].priority)
			{
				_threads[i].thread->run();
			}
		}
		else
		{
			_runCount[i] = 0;
		}
	}
}


/*

Scheduler::Scheduler(Coms* theComs, ComsEncoder* theComsEncoder, AccGyro* theAccGyro, Indicator* theIndicator, Lidar* theLidar)
{
	_coms = theComs;
	_comsEncoder = theComsEncoder;

	_accGyro = theAccGyro;
	_accPriority = 1;
	_accRunCount = 0;

	_indicator = theIndicator;
	_indicatorPriority = 1;
	_indicatorRunCount = 0;

	_lidar = theLidar;
	_lidarPriority = 1;
	_lidarRunCount = 0;
}

void Scheduler::setAccPriority(int p)
{
	_accPriority = p;
}

void Scheduler::setIndicatorPriority(int p)
{
	_indicatorPriority = p;
}

void Scheduler::setLidarPriority(int p)
{
	_lidarPriority = p;
}


void Scheduler::run()
{
	// top priority
	_coms->run();
	_comsEncoder->run();

	//Serial.println("Enter");

	//acc
	if (_accPriority != 0)
	{
		_accRunCount++;
		if (_accRunCount >= _accPriority)
		{
			_accGyro->run();
			_accRunCount = 0;
		}
	}
	else
	{
		_accRunCount = 0;
	}

	//Serial.println("Done Acc");

	//indicator
	if (_indicatorPriority != 0)
	{
		_indicatorRunCount++;
		if (_indicatorRunCount >= _indicatorPriority)
		{
			_indicator->run();
			_indicatorRunCount = 0;
		}
	}
	else
	{
		_indicatorRunCount = 0;
	}

	//Serial.println("Done Indicator");

	//lidar
	if (_lidarPriority != 0)
	{
		_lidarRunCount++;
		if (_lidarRunCount >= _lidarPriority)
		{
			//_lidar->run();
			_lidarRunCount = 0;
		}
	}
	else
	{
		_lidarRunCount = 0;
	}
	
	//Serial.println("Done Lidar");
}

*/