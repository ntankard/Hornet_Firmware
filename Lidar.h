#pragma once

#include "Runnable.h"
#include "Arduino.h"
#include "LidarComs.h"
#include "Error.h"
#include "CONFIG.h"
#include "MessageBuffer.h"
#include "CollisionAvoidance.h"

class Lidar : public Runnable
{
public:
	Lidar(volatile Error* e);

	int getNORegisters(){ return 2; }
	volatile MessageBuffer_Passer* getRegister()
	{ 
		if (_registerRead == 0)
		{
			_registerRead++;
			return &_lastLidarRegister;
		}
		else
		{
			return _avoidance.getRegister();
		}
		return &_lastLidarRegister; 
	}
	void addRegister(volatile MessageBuffer_Passer* newRegister){}

	bool start();
	bool run();

	int getTotalCount(){ return _lidarComs.getTotalCount(); }
	int getMissed(){ return _lidarComs.getMissed(); }
	void setTotalCount(int toSet){ _lidarComs.setTotalCount(toSet); }
	void setMissed(int toSet){ _lidarComs.setMissed(toSet); }



	/*bool start();
	int run();
	volatile MessageBuffer_Passer* getMessage()volatile { return _toSend; }*/

private:

	int _registerRead;
	MessageBuffer<MB_LAST_LIDAR, 2> _lastLidarRegister;

	LidarComs _lidarComs;

	CollisionAvoidance _avoidance;

	int _lastAngle;
	
};

