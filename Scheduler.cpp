#include "Scheduler.h"

Scheduler::Scheduler(Error *e)
{
	_e = e;
	_setCount = 0;
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		_runCount[i] = 0;
		_threads[i].thread = NULL;
		_threads[i].priority = 1;
	}
}

void Scheduler::addRunable(int ID, Runnable *theRunnable)
{
	if (theRunnable == NULL)
	{
		_e->add(E_SETUP_ERROR, "Attempting to add a null runable");
		return;
	}

	if (_threads[ID].thread != NULL)
	{
		_e->add(E_SETUP_ERROR, "Attempting to overwright a existing thread" + (String)ID);
		return;
	}

	_threads[ID].thread = theRunnable;
	_threads[ID].priority = 1;
	_setCount++;
}

bool Scheduler::finish()
{
	return !(_setCount == C_SCHEDULER_THREAD_NUM);
}

void Scheduler::setPriority(int ID, int p)
{
	_threads[ID].priority = p;
}

void Scheduler::run()
{
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		if (_threads[i].priority != 0)
		{
			_runCount[i]++;
			if (_runCount[i] >= _threads[i].priority)
			{
				_threads[i].thread->run();
			}
		}
		else
		{
			_runCount[i] = 0;
		}
	}
}
