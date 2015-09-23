#pragma once

#include "Runnable.h"
#include "Arduino.h"
#include "LidarComs.h"
#include "Error.h"
#include "MessageBuffer_Manager.h"
#include "CONFIG.h"

class Lidar : public Runnable
{
public:
	Lidar(volatile Error* e);
	bool start();
	int run();
	volatile MessageBuffer_Passer* getMessage()volatile { return _toSend; }

private:
	LidarComs _lidarComs;
	volatile MessageBuffer_Manager<MB_LIDAR_SETTING> _lidarSender;
	volatile MessageBuffer_Passer* _toSend;
	
};

