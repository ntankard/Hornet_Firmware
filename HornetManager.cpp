#include "HornetManager.h"
#include "Coms.h"
#include "ComsEncoder.h"
#include "AccGyro.h"
#include "Monitor.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- CONSTRUCTION ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

HornetManager::HornetManager()
{
	_state = Init;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::start()
{
	_accGyro->start();

	_state = Connect;
	_C_last = millis();
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
// --------------------------------------------------- NOTIFICATIONS ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void HornetManager::newAccGyro(float accel[3], float gyro[3])
{
	_monitor->newAccGyro(accel, gyro);
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::comsConnectionCOnfirmed()
{
	if (_state == Connect)
	{
		_state = Idle;
		_monitor->on();
	}
	else
	{
		//@TODO add error
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- MAIN LOOP ------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void HornetManager::run()
{	
	// run coms no matter what
	_coms->run();
	_comsEncoder->run();

	switch (_state)
	{
	case Init:
		break;
	case Connect:
		runConnect();
		break;
	default:
		break;
	}

	_accGyro->run();
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

