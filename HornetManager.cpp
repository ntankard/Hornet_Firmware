#include "HornetManager.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- CONSTRUCTION ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

HornetManager::HornetManager() :_scheduler(&_e), _indicator(&_e), _comsEncoder(&_e)
{
	_state = Init;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::start()
{

	// setup all scedual objects
	_scheduler.addRunable(C_SCHEDULER_INDICATOR_THREAD, &_indicator);
	_scheduler.addRunable(C_SCHEDULER_COMENCODER_THREAD, &_comsEncoder);
	_scheduler.addRunable(C_SCHEDULER_GYRO_THREAD, &_gyro);
	_scheduler.addRunable(C_SCHEDULER_FLIGHT_THREAD, &_theDrone);

	// log all non runnable registers
	_comsEncoder.addRegister(&_statusRegister);

	// start all objects
	if (!_scheduler.finish() || !_scheduler.startAll())
	{
		_indicator.safeOn();
		while (true)
		{
			DEBUG_PRINTLN("Not all objects attached");//@TODO add build exeption here
			delay(500);
		}
	}

	// transition to an operating state
	changeState(ST_TO_IDLE);			//@TODO conection state is bypasses
	_C_last = millis();
	_statusLast = _C_last;
}


//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- MAIN LOOP ------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void HornetManager::run()
{	
	unsigned long current = millis();
	_loopCount++;

	// exicute the threads
	_scheduler.run(); 

	// check for special logic
	if (_state == Connect)
	{
		runConnect();
	}
	else if (_state == Idle)
	{
		if (_theDrone.isArmed())
		{
			changeState(ST_TO_FLIGHT);
		}
	}
	else if (_state == Flight)
	{
		if (!_theDrone.isArmed())
		{
			changeState(ST_TO_IDLE);
		}
	}

	// catch exeption
	if (_e.isError())
	{
		int line = _e.getError();
		_indicator.safeOn();
		while (true){
			DEBUG_PRINTLN("ERROR");
			DEBUG_PRINTLN((String)line);
			delay(500);
		}
	}

	// update the status
	if (_statusLast + 1000 <= current)
	{
		_statusRegister.getData()[0] = _state;
		_statusRegister.getData()[1] = _loopCount;

		_statusLast += 1000;
		_loopCount = 0;
	}

}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::changeState(State newState, int indicatorPriority, int comEncoderPri, int gyroPri, int flightPri, int lightSetting, int lightBlinks, int lightRate)
{
	_state = newState;

	_scheduler.setPriority(C_SCHEDULER_INDICATOR_THREAD, indicatorPriority);
	_scheduler.setPriority(C_SCHEDULER_COMENCODER_THREAD, comEncoderPri);
	_scheduler.setPriority(C_SCHEDULER_GYRO_THREAD, gyroPri);
	_scheduler.setPriority(C_SCHEDULER_FLIGHT_THREAD, flightPri);

	_indicator.setDisplay(0, lightSetting, lightBlinks, lightRate);

	_statusRegister.getData()[0] = _state;
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::runConnect()
{
	unsigned long current = millis();

	if (_C_last + C_CONNECT_PULSE_TIME <= current)
	{
		_C_last = current;
//	_comsEncoder.sendChar(C_COMS_CODE_CONNECT_REQUEST);
	}

}

/*

void HornetManager::newMessage(uint8_t data)
{
switch (data)
{
case C_COMS_CODE_CONNECT_CONFIRM:
if (_state == Connect)
{
changeState(ST_TO_IDLE);
}
break;
case MB_ARM_DISARM:
if (_state == Idle)
{
_theDrone.arm();
takeOff();
}
else if (_state = Flight)
{
_theDrone.disarm();
changeState(ST_TO_IDLE);
}
break;
default:
break;
}
}

void HornetManager::takeOff()
{
changeState(ST_TO_TAKEOFF);

changeState(ST_TO_FLIGHT);
}

void HornetManager::newData(volatile MessageBuffer_Passer* data)
{
if (data->isMonitor())
{
_comsEncoder.sendData(data);
}

if (data->getDataSize() == 0)
{
newMessage(data->getID());
}

switch (data->getID())
{
case MB_JOY_XY:
//_theDrone.newPitchRoll(data->getData()[0], data->getData()[1]);
_theDrone.newJoyXY(data);
break;
case MB_JOY_Z:
_theDrone.newJoyZ(data);
//newData(_theDrone.newYaw(data->getData()[0]));
break;
case MB_JOY_THROTTLE:
//_theDrone.newThrottle(data->getData()[0]);
//newData(_theDrone.newThrottle(data->getData()[0]));
_theDrone.newJoyThrottle(data);
break;
case MB_ROLL_PITCH_YAW:
_theDrone.newGyro(data);
break;
case MB_ARM_DISARM:
if (data->getData()[0] == 1)
{
if (_state == Idle)
{
_theDrone.arm();
TP("ARM");
}
}
else
{
if (_state == Flight)
{
_theDrone.disarm();
TP("DISARM");
}
}
default:
break;
}
}*/