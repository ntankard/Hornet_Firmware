#include "Scheduler.h"

Scheduler::Scheduler(volatile Error *e)
{
	_e = e;
	_setCount = 0;
	//_currentThread = C_SCHEDULER_THREAD_NUM;
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		_currentThreadI.setPriority(i, -1);
		//_runCount[i] = 0;
		_threads[i].priority = -1;
		_threadCount[i] = 0;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void Scheduler::addRunable(int ID, Runnable *theRunnable)
{
	if (ID >= C_SCHEDULER_THREAD_NUM || ID <0)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
	}else if (_threads[ID].priority != -1)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
	}
	else{

		_threads[ID].thread = theRunnable;
		_threads[ID].priority = 1;
		_currentThreadI.setPriority(ID, 1);
		_setCount++;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Scheduler::finish()
{
	if ((_setCount == C_SCHEDULER_THREAD_NUM))
	{
		for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
		{
			for (int r = 0; r < _threads[i].thread->getNORegisters(); r++)
			{
				volatile MessageBuffer_Passer* toDistribute = _threads[i].thread->getRegister();
				for (int j = 0; j < C_SCHEDULER_THREAD_NUM; j++)
				{
					if (i != j)
					{
						_threads[j].thread->addRegister(toDistribute);
					}
				}
			}
		}

		for (int j = 0; j < C_SCHEDULER_THREAD_NUM; j++)
		{
			_threads[j].thread->addRegister(&_schedularRegister);
		}

		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Scheduler::startAll()
{
	if (_setCount == C_SCHEDULER_THREAD_NUM)
	{
		for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
		{
			if (!_threads[i].thread->start())
			{
				return false;
			}
		}
		return true;
	}
	_e->add(E_NULL_PTR, __LINE__);
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Scheduler::setPriority(int ID, int p)
{
	if (ID >= C_SCHEDULER_THREAD_NUM || ID <0)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
	}
	_currentThreadI.setPriority(ID, p);
	_threads[ID].priority = p;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Scheduler::run()
{
	int i = _currentThreadI.getNextIndex();
	_threadCount[i]++;
	return _threads[i].thread->run();

	// keep looping until a thread runs (this will lock if all thread are 0)
	/*while (true){

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
	}*/
	//return false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Scheduler::resetCount()
{
	for (int i = 0; i < C_SCHEDULER_THREAD_NUM; i++)
	{
		_schedularRegister.getData()[i] = _threadCount[i];
		_threadCount[i] = 0;
	}
}
