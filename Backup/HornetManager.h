#pragma once
#include "Error.h"
#include "MessageBuffer_Passer.h"

// forward declare to prevent circular dependancy
class Coms;
class ComsEncoder;
class AccGyro;
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


	void attachComs(Coms* theComs);
	void attachComsEncoder(ComsEncoder* theComsEncoder);

	void attachAccGyro(AccGyro* theAccGyro);
	void attachIndicator(Indicator* theIndicator);
	void attachMagnetometer(Magnetometer *theMagnetometer);

	void attachScheduler(Scheduler* theScheduler);

	void newData(MessageBuffer_Passer *data);

	//void ND_RawAccGyro(float accel[3], float gyro[3]);

	//void ND_RawMag(int16_t *mag);

	//void ND_Yaw(double theYaw);
	
	void ND_Throttle(int t);

	void M_ConnectionConfirmed();
	void M_ArmDisarm();
	void M_Reset();

	bool run();


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

	Scheduler* _scheduler;
	Error *_e;

	Coms* _coms;
	ComsEncoder* _comsEncoder;

	AccGyro* _accGyro;
	Indicator* _indicator;
	Magnetometer *_magnetometer;

	unsigned long _C_last;
	bool _isReset;
	bool _monitor;
};
