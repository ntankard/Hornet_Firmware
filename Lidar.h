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

/**
* \class	Lidar
*
* \brief	Manage the operations of a RPLIDAR device
*/
class Lidar : public Runnable
{
public:
	Lidar(volatile Error* e);

	// standard runnable methods
	int getNORegisters(){ return 6; }
	volatile MessageBuffer_Passer* getRegister();
	void addRegister(volatile MessageBuffer_Passer* newRegister){}
	bool start();
	bool run();

	// packet loss monitoring
	int getTotalCount(){ return _lidarComs.getTotalCount(); }
	int getMissed(){ return _lidarComs.getMissed(); }
	void setTotalCount(int toSet){ _lidarComs.setTotalCount(toSet); }
	void setMissed(int toSet){ _lidarComs.setMissed(toSet); }

private:

	/** \brief	The object used to comunicate with the LIDAR */
	LidarComs _lidarComs;

	/** \brief	The object used to cacualte position from the LIDAR data */
	LidarNavigation _nav;

	/** \brief	The object used to cacualte avoidance vectors from the LIDAR data */
	CollisionAvoidance _avoidance;

	/** \brief	The angle of the last lidar point */
	int _lastAngle;

	/** \brief	Track the number of points read */
	int _readCount;

	/** \brief	Track the number of registers read by getRegister() */
	int _registerRead;

	/** \brief	The last read lidar point in POLAR form */
	MessageBuffer<MB_LAST_LIDAR, 2> _lastLidarRegister;
	
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

