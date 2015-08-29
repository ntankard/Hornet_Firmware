#pragma once
#include "Error.h"

// forward declare to prevent circular dependancy
class Coms;
class ComsEncoder;
class AccGyro;
class Monitor;
class Indicator;
class Scheduler;
class Magnetometer;

enum State{ Init, Connect, Idle ,TakeOff,Flight,Land,Emergency,Crash};

class HornetManager
{
public:

	/**
	 * \fn	HornetManager::HornetManager();
	 *
	 * \brief	Creates the static objects in the manager, certain componets must be added after constuction then setup can run
	 *
	 * \author	Nicholas
	 * \date	29/07/2015
	 */
	HornetManager(Error *theError);

	/**
	 * \fn	void HornetManager::start();
	 *
	 * \brief	Complets the construction after all object have been created and attached
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 */
	void start();

	/**
	 * \fn	void HornetManager::attachComs(Coms* theComs);
	 *
	 * \brief	Attach a pre constructed coms object that holds a refrence to this manager instance
	 *
	 * \author	Nicholas
	 * \date	29/07/2015
	 *
	 * \param [in,out]	theComs	If non-null, the coms.
	 */
	void attachComs(Coms* theComs);
	void attachComsEncoder(ComsEncoder* theComsEncoder);
	void attachAccGyro(AccGyro* theAccGyro);
	void attachMonitor(Monitor* theMonitor);
	void attachIndicator(Indicator* theIndicator);
	void attachScheduler(Scheduler* theScheduler);
	void attachMagnetometer(Magnetometer *theMagnetometer);

	void ND_RawAccGyro(float accel[3], float gyro[3]);
	
	void ND_Throttle(int t);

	void M_ConnectionConfirmed();

	void M_ArmDisarm();

	void ND_PitchRoll(float pitch, float roll);

	void ND_LidarData(float yaw, float distance, float pitch);

	void ND_LidarPoint(float angle, float distance);

	void ND_LidarEOSweep(float pitch, float roll, float yaw);

	bool run();

	void M_Reset();
private:

	void runConnect();


	void S_enterInit();
	void S_initToConnect();

	void S_enterConnect();
	void S_connectToIdle();

	void S_enterIdle();
	void S_idleToConnect();
	void S_idleToInit();
	void S_idleToTakeOff();

	void S_enterTakeOff();
	void S_takeOffToFlight();

	void S_enterFlight();
	void S_flightToLand();
	void S_flightToEmergency();

	void S_enterLand();
	void S_landToIdle();

	void S_enterEmergency();
	void S_emergencyToCrash();

	void S_enterCrash();
	void S_crashToInit();

	State _state;

	Coms* _coms;
	ComsEncoder* _comsEncoder;
	AccGyro* _accGyro;
	Monitor* _monitor;
	Indicator* _indicator;
	Scheduler* _scheduler;
	Magnetometer *_magnetometer;

	Error *_e;

	unsigned long _C_last;

	bool _isReset;
};

