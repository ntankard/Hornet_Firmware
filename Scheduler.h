#pragma once
#include "Coms.h"
#include "ComsEncoder.h"
#include "AccGyro.h"
#include "Indicator.h"

class Scheduler
{
public:
	Scheduler(Coms* theComs, ComsEncoder* theComsEncoder, AccGyro* theAccGyro, Indicator* theIndicator);

	void setAccPriority(int p);

	void setIndicatorPriority(int p);

	void run();

private:

	Coms* _coms;
	ComsEncoder* _comsEncoder;

	int _accPriority;
	int _accRunCount;
	AccGyro* _accGyro;

	int _indicatorPriority;
	int _indicatorRunCount;
	Indicator* _indicator;

};
