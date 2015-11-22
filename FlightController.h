#pragma once

#include "Runnable.h"
#include "MessageBuffer.h"
#include "TimeOut.h"
#include <Servo.h>

enum FlightState{ Disarmed = 0, Arming = 1, Armed = 2, Disarming = 3};

/**
* \brief	Forward flight commands onto the stabilizer
*/
class FlightController : public Runnable
{
public:
	FlightController();

	// standard runnable methods
	int getNORegisters(){ return 2; }
	volatile MessageBuffer_Passer* getRegister()
	{ 
		if (_regReadCount == 0)
		{
			_regReadCount++;
			return &_JoyVector;
		}
		else
		{
			return &_TotalVector;
		}
	}
	void addRegister(volatile MessageBuffer_Passer* newRegister);
	bool start();
	bool run();

	/**
	* \brief	Gets the current state of the controller
	*/
	FlightState getState(){ return _state; }

private:

	/**
	* \brief	Send the command to arm the engines (takes 5 seconds non blocking)
	*/
	void arm();

	/**
	* \brief	Send the command to disarm the engines (takes 3 seconds non blocking)
	*/
	void disarm();

	FlightState _state;
	TimeOut _armTime;

	// connections to the stabilizer
	Servo _roll;
	Servo _pitch;
	Servo _yaw;
	Servo _throttle;

	// joystick input
	volatile MessageBuffer_Passer* _throttleJoyRegister;
	volatile MessageBuffer_Passer* _XYJoyRegister;
	volatile MessageBuffer_Passer* _ZJoyRegister;
	volatile MessageBuffer_Passer* _ArmDisarmRegister;
	volatile MessageBuffer_Passer* _AvoidRegister;

	// flight safety input
	volatile MessageBuffer_Passer* _CompensationVector;

	// control settings monitor
	volatile MessageBuffer<MB_JOY_VECTOR, 2> _JoyVector;
	volatile MessageBuffer<MB_TOTAL_VECTOR, 2> _TotalVector;

	/** \brief	Track the number of registers read by getRegister()*/
	int _regReadCount;
};

