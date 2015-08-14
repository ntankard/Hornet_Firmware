#pragma once
#include "HornetManager.h"
#include "Arduino.h"
#include <RPLidar.h>

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