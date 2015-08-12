#include "Scheduler.h"


Scheduler::Scheduler(Coms* theComs, ComsEncoder* theComsEncoder, AccGyro* theAccGyro, Indicator* theIndicator)
{
	_coms = theComs;
	_comsEncoder = theComsEncoder;

	_accGyro = theAccGyro;
	_accPriority = 1;
	_accRunCount = 0;

	_indicator = theIndicator;
	_indicatorPriority = 1;
	_indicatorRunCount = 0;
}

void Scheduler::setAccPriority(int p)
{
	_accPriority = p;
}

void Scheduler::setIndicatorPriority(int p)
{
	_indicatorPriority = p;
}


void Scheduler::run()
{
	// top priority
	_coms->run();
	_comsEncoder->run();

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
	

}
