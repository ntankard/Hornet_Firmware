#include "HornetManager.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- CONSTRUCTION ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

HornetManager::HornetManager() :_scheduler(&_e), _indicator(&_e), _comsEncoder(&_e), _LIDAR(&_e)
{
	_state = Init;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::start()
{
	// link all scedual objects
	_scheduler.addRunable(C_SCHEDULER_INDICATOR_THREAD, &_indicator);
	_scheduler.addRunable(C_SCHEDULER_COMENCODER_THREAD, &_comsEncoder);
	_scheduler.addRunable(C_SCHEDULER_GYRO_THREAD, &_gyro);
	_scheduler.addRunable(C_SCHEDULER_FLIGHT_THREAD, &_theDrone);
	_scheduler.addRunable(C_SCHEDULER_LIDAR_THREAD, &_LIDAR);

	// log all non runnable registers
	_comsEncoder.addRegister(&_statusRegister);

	// finalize the linking process
	if (!_scheduler.finish())
	{
		_indicator.safeOn();
		while (true)
		{
			COM_SERIAL.println("Not all objects attached");
			DEBUG_PRINTLN("Not all objects attached");
			delay(500);
		}
	}

	// start all threads
	if (!_scheduler.startAll())
	{
		_indicator.safeOn();
		while (true)
		{
			COM_SERIAL.println("Object failed to start");
			DEBUG_PRINTLN("Object failed to start");
			delay(500);
		}
	}

	// transition to an operating state
	changeState(ST_TO_IDLE);
}

//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- MAIN LOOP ------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void HornetManager::run()
{	
	// run the main program
	_scheduler.run(); 

	// check for state change
	switch (_theDrone.getState())
	{
	case Armed:
		if (_state != Flight)
		{
			changeState(ST_TO_FLIGHT);
		}
		break;
	case Arming:
		if (_state != TakeOff)
		{
			changeState(ST_TO_TAKEOFF);
		}
		break;
	case Disarmed:
		if (_state != Idle)
		{
			changeState(ST_TO_IDLE);
		}
		break;
	case Disarming:
		if (_state != Land)
		{
			changeState(ST_TO_LAND);
		}
		break;
	default:
		break;
	}

	// catch exeption
	if (_e.isError())
	{
		if (_state != Armed)
		{
			int line = _e.getError();
			_indicator.safeOn();
			while (true){
				COM_SERIAL.println("ERROR");
				COM_SERIAL.println((String)line);
				DEBUG_PRINTLN("ERROR");
				DEBUG_PRINTLN((String)line);
				delay(500);
			}
		}
	}

	// monitor the speed of the program
	unsigned long current = millis();
	_loopCount++;
	if (_statusLast + 1000 <= current)
	{
		_statusRegister.getData()[1] = _loopCount;
		_statusRegister.getData()[2] = _comsEncoder.getSendCount();
		_statusRegister.getData()[3] = _LIDAR.getTotalCount();
		_statusRegister.getData()[4] = _LIDAR.getMissed();
		_comsEncoder.setSendCound(0);
		_LIDAR.setMissed(0);
		_LIDAR.setTotalCount(0);
		_statusLast += 1000;
		_loopCount = 0;
		_scheduler.resetCount();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::changeState(State newState, int indicatorPriority, int comEncoderPri, int gyroPri, int flightPri,int lidarPri, int lightSetting, int lightBlinks, int lightRate)
{
	_state = newState;
	_statusRegister.getData()[0] = _state;

	_scheduler.setPriority(C_SCHEDULER_INDICATOR_THREAD, indicatorPriority);
	_scheduler.setPriority(C_SCHEDULER_COMENCODER_THREAD, comEncoderPri);
	_scheduler.setPriority(C_SCHEDULER_GYRO_THREAD, gyroPri);
	_scheduler.setPriority(C_SCHEDULER_FLIGHT_THREAD, flightPri);
	_scheduler.setPriority(C_SCHEDULER_LIDAR_THREAD, lidarPri);

#ifdef USE_DM_INDICATOR
	_indicator.setDisplay(0, lightSetting, lightBlinks, lightRate);
#else
	_indicator.setDisplay(lightSetting, lightBlinks, lightRate);
#endif
}