#include "HornetManager.h"

//-----------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- CONSTRUCTION ----------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

HornetManager::HornetManager(Error *theError) :_scheduler(theError), _indicator(theError)
{
	_e = theError;
	_state = Init;

	_scheduler.addRunable(C_SCHEDULER_INDICATOR_THREAD, &_indicator);
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::start()
{
	if (!_scheduler.finish())
	{
		while (true)
		{
			TP("Not all objects attached");//@TODO add build exeption here
			delay(500);
		}
	}
	if (!_scheduler.startAll())
	{
		while (true)
		{
			TP("Failed to start");//@TODO add build exeption here
			delay(500);
		}
	}

	changeState(ST_TO_CONNECT);

	_indicator.on();
}


//-----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- MAIN LOOP ------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void HornetManager::run()
{	
	// exicute the threads
	_scheduler.run(); 

	int line;
	// catch exeption
	if (_e->isError())
	{
		line = _e->getError();
		while (true){
			TP("ERROR");
			TP((String)line)
				delay(500);
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void HornetManager::changeState(State newState, int indicatorPriority, int lightSetting, int lightBlinks, int lightRate)
{
	_state = newState;

	_scheduler.setPriority(C_SCHEDULER_INDICATOR_THREAD, indicatorPriority);

	_indicator.setDisplay(0, lightSetting, lightBlinks, lightRate);
}
