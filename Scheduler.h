#pragma once
#include "Runnable.h"
#include "Config.h"
#include "Error.h"
#include "PriorityManager.h"
#include "MessageBuffer.h"

/**
* \brief	A thread and its priority
*/
struct thread_settings
{
	Runnable * volatile thread;
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
	* \brief	Default constructor
	*/
	Scheduler(volatile Error *e);

	/**
	* \brief	Constructor for the MPU6050
	*
	* \param	ID				The ID of the thread
	* \param	theRunnable		The thread
	*
	* \throw	E_SETUP_ERROR	If the thread is null or it's attempting to overwrite another thread
	*/
	void addRunable(int ID, Runnable *theRunnable);

	/**
	* \brief	Solidifies the scheduler after all runnables are added
	*
	* \return	true if all threads are acounted for
	*/
	bool finish();

	/**
	* \brief	Solidifies the scheduler after all runnables are added
	*
	* \return	true if all threads are accounted for
	*/
	bool startAll();

	/**
	* \brief	Set the priority of a specific thread
	*
	* \param	ID				The ID of the thread
	* \param	p				The priority to set
	*
	* \throw E_INDEX_OOB		If the ID is invalid
	*/
	void setPriority(int ID, int p);

	/**
	* \brief	Execute each thread at its priority
	*/
	bool run();


	/**
	* \brief	Reset the monitoring variables
	*/
	void resetCount();

private:

	/** \brief	The shared error object */
	volatile Error *_e;

	/** \brief	All of the thread (runnable classes) */
	Thread_Settings _threads[C_SCHEDULER_THREAD_NUM];

	/** \brief	How many threads have been registered (used to ensure no missing threads when the system starts) */
	int _setCount;

	/** \brief	Track what order the threads should run in (high priority runs more often) */
	PriorityManager<C_SCHEDULER_THREAD_NUM> _currentThreadI;

	/** \brief	The number of times each thread has run (for performance monitoring) */
	volatile MessageBuffer<MB_SCHEDULAR_MONITOR, C_SCHEDULER_THREAD_NUM> _schedularRegister;

	/** \brief	Real time measuring for the above */
	int _threadCount[C_SCHEDULER_THREAD_NUM];
};

