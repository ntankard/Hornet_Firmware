#include "Scheduler.h"

Scheduler::Scheduler(Error *e)
{
	_e = e;
	_setCount = 0;
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		_runCount[i] = 0;
		_threads[i].priority = -1;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void Scheduler::addRunable(int ID, Runnable *theRunnable)
{
	if (ID >= C_SCHEDULER_THREAD_NUM || ID <0)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
		return;
	}

	if (_threads[ID].priority != -1)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
		return;
	}

	_threads[ID].thread = theRunnable;
	_threads[ID].priority = 0;
	_setCount++;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Scheduler::finish()
{
	return (_setCount == C_SCHEDULER_THREAD_NUM);
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Scheduler::startAll()
{
	if (!finish())
	{
		_e->add(E_NULL_PTR, __LINE__);
		return false;
	}

	for (int i = 0; i < C_SCHEDULER_THREAD_NUM;i++)
	{
		if (!_threads[i].thread->start())
		{
			return false;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Scheduler::setPriority(int ID, int p)
{
	if (ID >= C_SCHEDULER_THREAD_NUM || ID <0)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
	}
	_threads[ID].priority = p;
}

//-----------------------------------------------------------------------------------------------------------------------------

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
