#include "Drone.h"


Drone::Drone()
{
}

void Drone::start()
{
	_frontLeft.attach(C_MOTOR_FRONT_LEFT);
	_frontRight.attach(C_MOTOR_FRONT_RIGHT);
	_backLeft.attach(C_MOTOR_BACK_LEFT);
	_backRight.attach(C_MOTOR_BACK_RIGHT);

	_frontLeft.write(0);
	_frontRight.write(0);
	_backLeft.write(0);
	_backRight.write(0); 
	_isArmed = false;
}

void Drone::arm()
{
	_frontLeft.write(IDLE);
	_frontRight.write(IDLE);
	_backLeft.write(IDLE);
	_backRight.write(IDLE);
	_isArmed = false;
}

void Drone::disarm()
{
	_frontLeft.write(0);
	_frontRight.write(0);
	_backLeft.write(0);
	_backRight.write(0);
	_isArmed = false;
}

void Drone::setThrottle(int p)
{
	double range = MAX - IDLE;

	double setting = range*((double)p / 100.0);

	_frontLeft.write(setting + IDLE);
	_frontRight.write(setting + IDLE);
	_backLeft.write(setting + IDLE);
	_backRight.write(setting + IDLE);
}

Drone::~Drone()
{
}
