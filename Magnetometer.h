#pragma once
#include "CONFIG.h"

#if ENABLE_MAG == ENABLED

#include "MicroMag3.h"
#include "SPIManager.h"

class Magnetometer
{
public:
	Magnetometer(SPIManager *theSPIManager);
	bool start();
	void run();
private:
	MicroMag3 _mag;
};

#else

#endif
