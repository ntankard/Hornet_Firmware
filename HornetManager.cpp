#include "HornetManager.h"
#include "Coms.h"
#include "ComsEncoder.h"
#include "AccGyro.h"
#include "Monitor.h"
#include "Indicator.h"
#include "Scheduler.h"
#include <Arduino.h>
#include "Servo.h"
#include "APM_Indicator.h"
#include "Magnetometer.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- CONSTRUCTION ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

HornetManager::HornetManager(Error *theError)
{
	_e = theError;
	S_enterInit();
	_isReset = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::attachComs(Coms* theComs){_coms = theComs;}
void HornetManager::attachComsEncoder(ComsEncoder* theComsEncoder){_comsEncoder = theComsEncoder;}
void HornetManager::attachAccGyro(AccGyro* theAccGyro){	_accGyro = theAccGyro;}
void HornetManager::attachMonitor(Monitor* theMonitor){	_monitor = theMonitor;}
void HornetManager::attachIndicator(Indicator* theIndicator){	_indicator = theIndicator;}
void HornetManager::attachScheduler(Scheduler* theScheduler){	_scheduler = theScheduler;}
void HornetManager::attachMagnetometer(Magnetometer *theMagnetometer){ _magnetometer = theMagnetometer; }

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::start()
{
	S_initToConnect();
}

//-----------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- NOTIFICATIONS ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void HornetManager::newData(MessageBuffer_Passer *data)
{
	if (data->isMonitor())
	{
		_comsEncoder->sendData(data);
	}

//	monitor->newData(data);

	switch (data->getID())
	{
	default:
		break;
	}
}



void HornetManager::ND_Throttle(int t)
{
	//@TODO impliment
}



//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::M_ConnectionConfirmed()
{
	S_connectToIdle();
}

void HornetManager::M_Reset()
{
	if (_state == Idle)
	{
		_isReset = true;	//@TODO add saftey check
	}
	else
	{
		//@TODO notify the base station that eh reset has been rejected for saftey reasons
	}
}

void HornetManager::M_ArmDisarm()
{
	if (_state == Idle)
	{
		S_idleToTakeOff();
		return;
	}

	if (_state == Flight)
	{
		//@TODO add can land check to prevent crash
		S_flightToLand();
		return;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- MAIN LOOP ------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

bool HornetManager::run()
{	
	// run the threads
	if (_state != Init)
	{
		_scheduler->run();
	}

	// check for special logic
	if (_state == Connect)
	{
		runConnect();
	}

	// catch exeption
	if (_e->isError())
	{
		_indicator->setDisplay(C_INDICATE_ERROR);
		while (true)
		{
			delay(10);
			String message = _e->getError()->errorInfo;
			Serial.println(message);
		}
		//@TODO add error handeling here
	}

	// end if reset
	return !_isReset;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::runConnect()
{
	unsigned long current = millis();

	if (_C_last + C_CONNECT_PULSE_TIME <= current)
	{
		_C_last = current;
		_comsEncoder->sendChar(C_COMS_CODE_CONNECT_REQUEST);
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

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::S_initToConnect()
{
	if (_state == Init)
	{
		_accGyro->start();
		_magnetometer->start();
		_C_last = millis();
		S_enterConnect();
	}
	else
	{
		_e->add(E_STATE_ERROR, "S_initToConnect called from a non init state");
	}
}

//---------------------------------------------------- CONNECT STATE ---------------------------------------------------------

void HornetManager::S_enterConnect()
{

	// threads
	_scheduler->setPriority(C_SCHEDULER_COMS_THREAD, 1);
	_scheduler->setPriority(C_SCHEDULER_COMENCODER_THREAD, 1);
	_scheduler->setPriority(C_SCHEDULER_ACCGYRO_THREAD, 0);
	_scheduler->setPriority(C_SCHEDULER_INDICATOR_THREAD, 2);
	_scheduler->setPriority(C_SCHEDULER_MAG_THREAD, 0);

	// extra systems
	_monitor->off();
	_indicator->on();
	_indicator->setDisplay(C_STATE_INDICATE_CONNECT);

	// state indicator
	_state = Connect;
}

//-----------------------------------------------------------------------------------------------------------------------------

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
		_e->add(E_STATE_ERROR, "S_connectToIdle called from a non Connect state");
	}
}

//------------------------------------------------------ IDLE STATE -----------------------------------------------------------

void HornetManager::S_enterIdle()
{
	// threads
	_scheduler->setPriority(C_SCHEDULER_COMS_THREAD, 1);
	_scheduler->setPriority(C_SCHEDULER_COMENCODER_THREAD, 1);
	_scheduler->setPriority(C_SCHEDULER_ACCGYRO_THREAD, 1);
	_scheduler->setPriority(C_SCHEDULER_INDICATOR_THREAD, 10);
	_scheduler->setPriority(C_SCHEDULER_MAG_THREAD, 1);


	// extra systems
	_monitor->on();
	_indicator->on();
	_indicator->setDisplay(C_STATE_INDICATE_IDLE);

	// state indicator
	_state = Idle;
}
void HornetManager::S_idleToConnect(){}
void HornetManager::S_idleToInit(){}
void HornetManager::S_idleToTakeOff()
{
	S_enterTakeOff();
}

void HornetManager::S_enterTakeOff()
{
	S_takeOffToFlight();	//@do nothing
}
void HornetManager::S_takeOffToFlight()
{
	S_enterFlight();
}

void HornetManager::S_enterFlight()
{
	// threads
	_scheduler->setPriority(C_SCHEDULER_COMS_THREAD, 1);
	_scheduler->setPriority(C_SCHEDULER_COMENCODER_THREAD, 1);
	_scheduler->setPriority(C_SCHEDULER_ACCGYRO_THREAD, 1);
	_scheduler->setPriority(C_SCHEDULER_INDICATOR_THREAD, 10);
	_scheduler->setPriority(C_SCHEDULER_MAG_THREAD, 1);

	// extra systems
	_monitor->on();
	_indicator->on();
	_indicator->setDisplay(C_STATE_INDICATE_FLIGHT);

	// state indicator
	_state = Flight;
}
void HornetManager::S_flightToLand()
{
	S_enterLand();
}
void HornetManager::S_flightToEmergency(){}

void HornetManager::S_enterLand()
{
	S_landToIdle();
}
void HornetManager::S_landToIdle()
{
	S_enterIdle();
}

void HornetManager::S_enterEmergency(){}
void HornetManager::S_emergencyToCrash(){}

void HornetManager::S_enterCrash(){}
void HornetManager::S_crashToInit(){}
