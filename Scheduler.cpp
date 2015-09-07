#include "Scheduler.h"

Scheduler::Scheduler(volatile Error *e)
{
	_e = e;
	_setCount = 0;
	_currentThread = C_SCHEDULER_THREAD_NUM;
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

int Scheduler::run()
{

	// keep looping until a thread runs (this will lock if all thread are 0)
	while (true){
		_currentThread++;
		if (_currentThread >= C_SCHEDULER_THREAD_NUM)
		{
			_currentThread = 0;
		}

		if (_threads[_currentThread].priority != 0)
		{
			_runCount[_currentThread]++;
			if (_runCount[_currentThread] >= _threads[_currentThread].priority)
			{
				return _threads[_currentThread].thread->run();
			}
		}
		else
		{
			_runCount[_currentThread] = 0;
		}
	}
}

MessageBuffer_Passer *Scheduler::getData()
{
	//@TODO add count check here
	return _threads[_currentThread].thread->getMessage();
}
