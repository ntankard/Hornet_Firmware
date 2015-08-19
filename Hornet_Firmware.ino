// hardware libreys (do not remove)
#include <Servo.h>
#include <RPLidar.h>
#include <ArduinoUnit.h>

#define FOR_HARDWARE 1
#define FOR_TEST 2

#define BUILD_TYPE FOR_TEST

// local components
#include "HornetManager.h"
#include "ComsDecoder.h"
#include "Coms.h"
#include "ComsEncoder.h"
#include "AccGyro.h"
#include "Monitor.h"
#include "Indicator.h"
#include "Scheduler.h"
#include "Lidar.h"
#include "Drone.h"

#include "CONFIG.h"

#if BUILD_TYPE == FOR_HARDWARE

// core componenets
HornetManager *manager;
Error *error;

// coms systems
Coms *coms;
ComsDecoder *comsDecoder;
ComsEncoder *comsEncoder;

// periferal systerms
AccGyro *accGyro;
Monitor *monitor;
Indicator *indicator;
Lidar *lidar;
Drone *drone;

Scheduler *scheduler;

Servo _frontLeft;
Servo _frontRight;
Servo _backLeft;
Servo _backRight;


void setup()
{
	Serial.begin(9600);				//@TODO remove
	error = new Error();
	manager = new HornetManager(error);

	// construct the coms
	comsDecoder = new ComsDecoder(manager);
	coms = new Coms(comsDecoder);

	comsEncoder = new ComsEncoder(coms, error);
	manager->attachComs(coms);
	manager->attachComsEncoder(comsEncoder);

	// construct thew accselerator and gyro
	accGyro = new AccGyro(manager, error);
	manager->attachAccGyro(accGyro);

	// construct the monitor
	monitor = new Monitor(comsEncoder);
	manager->attachMonitor(monitor);

	// construct the indicator
	indicator = new Indicator();
	manager->attachIndicator(indicator);

	// construct the lidar
	lidar = new Lidar(manager);
	manager->attachLidar(lidar);

	drone= new Drone();
	manager->attachDrone(drone);

	// construct the scedulor
	scheduler = new Scheduler(coms, comsEncoder, accGyro, indicator, lidar);
	manager->attachScheduler(scheduler);

	// start all objest with threads
	manager->start();
}

void loop()
{
	if (manager->run())
	{

	}
	else
	{
		delete manager;
		delete error;
		delete coms;
		delete comsDecoder;
		delete comsEncoder;
		delete accGyro;
		delete monitor;
		delete indicator;
		delete scheduler;

		setup();
	}


}

#else

#include "Test_CircularBuffer.h"

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Test::run();
}

#endif
