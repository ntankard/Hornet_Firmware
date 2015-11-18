#pragma once

#include "Runnable.h"
#include "Arduino.h"
#include "LidarComs.h"
#include "Error.h"
#include "CONFIG.h"
#include "MessageBuffer.h"
#include "CollisionAvoidance.h"
#include "LidarNavigation.h"

#ifdef USE_LIDAR

class Lidar : public Runnable
{
public:
	Lidar(volatile Error* e);

	int getNORegisters(){ return 6; }
	volatile MessageBuffer_Passer* getRegister()
	{ 
		if (_registerRead == 0)
		{
			_registerRead++;
			return &_lastLidarRegister;
		}
		else if (_registerRead == 1)
		{
			_registerRead++;
			return _avoidance.getRegister();
		}
		else
		{
			_registerRead++;
			return _nav.getNextRegister();
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
	LidarNavigation _nav;

	CollisionAvoidance _avoidance;

	int _lastAngle;
	int _readCount;
	
};

#else

class Lidar : public Runnable
{
public:
	Lidar(volatile Error* e)
	{
		_CompensatorRegister.getData()[0] = 50;
		_CompensatorRegister.getData()[1] = 50;
		_lastLidarRegister.getData()[0] = 0;
		_lastLidarRegister.getData()[1] = 0;
	}

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
			return &_CompensatorRegister;
		}
		return &_lastLidarRegister;
	}
	void addRegister(volatile MessageBuffer_Passer* newRegister){}

	bool start(){ return true; }
	bool run(){ return false; }

	int getTotalCount(){ return 0; }
	int getMissed(){ return 0; }
	void setTotalCount(int toSet){ }
	void setMissed(int toSet){  }
private:

	int _registerRead;
	volatile MessageBuffer<MB_LAST_LIDAR, 2> _lastLidarRegister;
	volatile MessageBuffer<MB_COMPENSATOR_VECTOR, 2> _CompensatorRegister;
};

#endif

