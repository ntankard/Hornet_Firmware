#pragma once

#include "Runnable.h"
#include "Arduino.h"
#include "LidarComs.h"
#include "Error.h"
#include "CONFIG.h"
#include "MessageBuffer.h"

class Lidar : public Runnable
{
public:
	Lidar(volatile Error* e);

	int getNORegisters(){ return 1; }
	volatile MessageBuffer_Passer* getRegister(){ return &_lastLidarRegister; }
	void addRegister(volatile MessageBuffer_Passer* newRegister){}

	bool start();
	bool run();





	/*bool start();
	int run();
	volatile MessageBuffer_Passer* getMessage()volatile { return _toSend; }*/

private:

	MessageBuffer<MB_LAST_LIDAR, 2> _lastLidarRegister;

	LidarComs _lidarComs;
	
};

