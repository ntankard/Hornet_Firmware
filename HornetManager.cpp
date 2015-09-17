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

	// start all objects
	if (!_scheduler.finish() || !_scheduler.startAll())
	{
		_indicator.safeOn();
		while (true)
		{
			TP("Not all objects attached")//@TODO add build exeption here
			delay(500);
		}
	}

	// transition to an operating state
	changeState(ST_TO_IDLE);			//@TODO conection state is bypasses
	_C_last = millis();
	_statusLast = millis();
}


//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- MAIN LOOP ------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void HornetManager::run()
{	
	// exicute the threads
	int toRead = _scheduler.run(); 
	for (int i = 0; i < toRead; i++)
	{
		newData(_scheduler.getData());
	}

	// check for special logic
	if (_state == Connect)
	{
		runConnect();
	}

	// catch exeption
	if (_e.isError())
	{
		int line = _e.getError();
		_indicator.safeOn();
		while (true){
			TP("ERROR");
			TP((String)line)
				delay(500);
		}
	}

	// update the status
	unsigned long current = millis();
	if (_statusLast + 1000 <= current)
	{
		volatile MessageBuffer_Passer* toSend = _statusSender.getAvailable();
		toSend->getData()[0] = _state;
		newData(toSend);
		_statusLast += 1000;
	}
}

void HornetManager::newMessage(uint8_t data)
{
	switch (data)
	{
	case C_COMS_CODE_CONNECT_CONFIRM:
		if (_state == Connect)
		{
			changeState(ST_TO_IDLE);
		}
	default:
		break;
	}
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
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::changeState(State newState, int indicatorPriority, int comEncoderPri, int gyroPri, int lightSetting, int lightBlinks, int lightRate)
{
	_state = newState;

	_scheduler.setPriority(C_SCHEDULER_INDICATOR_THREAD, indicatorPriority);
	_scheduler.setPriority(C_SCHEDULER_COMENCODER_THREAD, comEncoderPri);
	_scheduler.setPriority(C_SCHEDULER_GYRO_THREAD, gyroPri);

	_indicator.setDisplay(0, lightSetting, lightBlinks, lightRate);
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::runConnect()
{
	unsigned long current = millis();

	if (_C_last + C_CONNECT_PULSE_TIME <= current)
	{
		_C_last = current;
		_comsEncoder.sendChar(C_COMS_CODE_CONNECT_REQUEST);
	}

}