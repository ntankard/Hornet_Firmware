#include "HornetManager.h"
#include "Coms.h"
#include "ComsEncoder.h"
#include "AccGyro.h"
#include "Monitor.h"
#include "Indicator.h"
#include "Scheduler.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- CONSTRUCTION ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

HornetManager::HornetManager()
{
	S_enterInit();
	isReset = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::attachComs(Coms* theComs)
{
	_coms = theComs;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::attachComsEncoder(ComsEncoder* theComsEncoder)
{
	_comsEncoder = theComsEncoder;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::attachAccGyro(AccGyro* theAccGyro)
{
	_accGyro = theAccGyro;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::attachMonitor(Monitor* theMonitor)
{
	_monitor = theMonitor;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::attachIndicator(Indicator* theIndicator)
{
	_indicator = theIndicator;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::attachScheduler(Scheduler* theScheduler)
{
	_scheduler = theScheduler;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::start()
{
	S_initToConnect();
}

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- NOTIFICATIONS ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void HornetManager::newAccGyro(float accel[3], float gyro[3])
{
	_monitor->newAccGyro(accel, gyro);
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::comsConnectionConfirmed()
{
	S_connectToIdle();
}

void HornetManager::reset()
{
	isReset = true;
}

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- MAIN LOOP ------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

bool HornetManager::run()
{	
	if (_state != Init)
	{
		_scheduler->run();
	}

	// special state case @TODO replace this
	switch (_state)
	{
	case Connect:
		runConnect();
		break;
	default:
		break;
	}

	return !isReset;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::runConnect()
{
	unsigned long current = millis();

	if (_C_last + C_CONNECT_PULSE_TIME <= current)
	{
		_C_last = current;
		_comsEncoder->sendConnectRequest();
	}

}

//-----------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------- STATES -------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------ INIT STATE -----------------------------------------------------------

void HornetManager::S_enterInit()
{
	_state = Init;
}
void HornetManager::S_initToConnect()
{
	if (_state == Init)
	{
		_accGyro->start();
		_C_last = millis();
		S_enterConnect();
	}
	else
	{
		//@TODO throw
	}
}

//---------------------------------------------------- CONNECT STATE ---------------------------------------------------------

void HornetManager::S_enterConnect()
{
	// threads
	_scheduler->setAccPriority(0);
	_scheduler->setIndicatorPriority(2);

	// extra systems
	_monitor->off();
	_indicator->on();
	_indicator->setDisplay(C_STATE_CONNECT);

	// state indicator
	_state = Connect;
}
void HornetManager::S_connectToIdle()
{
	if (_state == Connect)
	{
		_state = Idle;
		_monitor->on();
		S_enterIdle();
	}
	else
	{
		//@TODO throw
	}
}

//------------------------------------------------------ IDLE STATE -----------------------------------------------------------

void HornetManager::S_enterIdle()
{
	// threads
	_scheduler->setAccPriority(2);
	_scheduler->setIndicatorPriority(10);

	// extra systems
	_monitor->on();
	_indicator->on();
	_indicator->setDisplay(C_STATE_IDLE);

	// state indicator
	_state = Idle;
}
void HornetManager::S_idleToConnect(){}
void HornetManager::S_idleToInit(){}
void HornetManager::S_idleToTakeOff(){}

void HornetManager::S_enterTakeOff(){}
void HornetManager::S_takeOffToFlight(){}

void HornetManager::S_enterFlight(){}
void HornetManager::S_flightToLand(){}
void HornetManager::S_flightToEmergency(){}

void HornetManager::S_enterLand(){}
void HornetManager::S_landToIdle(){}

void HornetManager::S_enterEmergency(){}
void HornetManager::S_emergencyToCrash(){}

void HornetManager::S_enterCrash(){}
void HornetManager::S_crashToInit(){}
