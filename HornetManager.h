#pragma once
#include "Error.h"
#include "Scheduler.h"
#include "DM_Indicator.h"
#include "Serial_Coms.h"
#include "ComsEncoder.h"
#include "Gyro.h"
#include "Drone.h"

enum State{ Init = 0, Connect = 1, Idle =2,TakeOff=3,Flight=4,Land=5,Emergency=6,Crash=7};


class HornetManager
{
public:

	HornetManager();
	void start();
	void run();

	void newMessage(uint8_t data);
	void newData(volatile MessageBuffer_Passer* data);

private:

	void takeOff();

	void runConnect();

	void changeState(State newState, int indicatorPriority, int comEncoderPri, int gyroPri, int lightSetting, int lightBlinks, int lightRate);

	State _state;
	unsigned long _C_last;


	Scheduler _scheduler;
	volatile Error _e;

	// all other objects
	Indicator _indicator;
	ComsEncoder _comsEncoder;
	Gyro _gyro;

	unsigned long _statusLast;
	MessageBuffer_Manager<MB_STATUS_SETTINGS> _statusSender;

	//@TODO remove
	Drone _theDrone;
	
};

