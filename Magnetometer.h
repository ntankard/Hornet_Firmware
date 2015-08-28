#pragma once
#include "CONFIG.h"
#include "SPIManager.h"
#include "Runnable.h"
#if ENABLE_MAG == ENABLED

#include "MicroMag3.h"

class Magnetometer : public Runnable
{
public:
	Magnetometer(SPIManager *theSPIManager);
	bool start();
	void run();
private:
	MicroMag3 _mag;
};

#else

class Magnetometer : public Runnable
{
public:
	Magnetometer(SPIManager *theSPIManager);
	bool start(){return true;}
	void run(){}
};

#endif
