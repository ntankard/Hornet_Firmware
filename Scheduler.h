#pragma once
#include "Runnable.h"
#include "Config.h"
#include "Error.h"

/**
* \brief	A thread and its priority
*/
struct thread_settings
{
	Runnable *thread;
	int priority;
};

typedef struct thread_settings Thread_Settings;

/**
* \brief	Mimics a multi thread system
*/
class Scheduler
{
public:

	/**
	* \brief	Default constructor.
	*/
	Scheduler(volatile Error *e);

	/**
	* \brief	Constctor for the MPU6050
	*
	* \param	ID				The ID of the thread
	* \param	theRunnable		The thread
	*
	* \throw	E_SETUP_ERROR	If the thread is null or its atempting ot overwight anotehr thread
	*/
	void addRunable(int ID, Runnable *theRunnable);

	/**
	* \brief	Solidifys the scedular after all runables are added
	*
	* \return	true if all threads are acounted for
	*/
	bool finish();

	/**
	* \brief	Solidifys the scedular after all runables are added
	*
	* \return	true if all threads are acounted for
	*/
	bool startAll();

	/**
	* \brief	Set the priority of a spesific thread
	*
	* \param	ID				The ID of the thread
	* \param	p				The priority to set
	*
	* \throw E_INDEX_OOB		If the ID is invalid
	*/
	void setPriority(int ID, int p);

	/**
	* \brief	Exicute each thread at its priority
	*/
	int run();

	MessageBuffer_Passer *getData();

private:
	volatile Error *_e;
	Thread_Settings _threads[C_SCHEDULER_THREAD_NUM];
	int _setCount;
	int _runCount[C_SCHEDULER_THREAD_NUM];
	int _currentThread;
};

