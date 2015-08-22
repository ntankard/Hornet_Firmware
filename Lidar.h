#pragma once
#include "HornetManager.h"
#include "Arduino.h"
#include <RPLidar.h>

#if ENABLE_LIDAR == ENABLED

class Lidar
{
public:
	Lidar(HornetManager* theManager);
	void start();
	void run();

private:
	HornetManager* _hornetManager;
	RPLidar _lidar;

};

#else

class Lidar
{
public:
	Lidar(HornetManager* theManager){}
	void start(){}
	void run(){}
};

#endif