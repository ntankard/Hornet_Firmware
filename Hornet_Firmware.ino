// hardware libreys (do not remove)
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#include <RPLidar.h>
#include <ArduinoUnit.h>

#define FOR_HARDWARE 1
#define FOR_TEST 2

#define BUILD_TYPE FOR_HARDWARE

#if BUILD_TYPE == FOR_HARDWARE

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
#include "SPIManager.h"
#include "I2CManager.h"

#include "CONFIG.h"

// core componenets
HornetManager *manager;
Error *error;

// coms systems
Coms *coms;
ComsDecoder *comsDecoder;
ComsEncoder *comsEncoder;

SPIManager *spiManager;
I2CManager *i2cManager;

// periferal systerms
AccGyro *accGyro;
Monitor *monitor;
Indicator *indicator;
Lidar *lidar;
Drone *drone;

Scheduler *scheduler;

void setup()
{
	error = new Error();
	manager = new HornetManager(error);

	// construct the coms
	comsDecoder = new ComsDecoder(manager);
	coms = new Coms(comsDecoder);
	comsEncoder = new ComsEncoder(coms, error);
	manager->attachComs(coms);
	manager->attachComsEncoder(comsEncoder);

	// set up conection infurstructor for the sensors
	spiManager = new SPIManager(error);
	i2cManager = new I2CManager(error);

	// construct thew accselerator and gyro
	#if ENABLE_ACC == ENABLED
		#ifdef USE_MPU6000
				accGyro = new AccGyro(manager,error,spiManager,MPU6000_CS,MPU6000_INTERRUPT);
		#endif
		#ifdef USE_MPU6050
				accGyro = new AccGyro(manager,error,i2cManager,MPU6050_INTERRUPT);
		#endif
	#else
		accGyro = new AccGyro();
	#endif


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
	if (!manager->run())
	{
		delete manager;
		delete error;
		delete coms;
		delete comsDecoder;
		delete comsEncoder;
		delete spiManager;

		delete accGyro;
		delete monitor;
		delete indicator;
		delete lidar;
		delete drone;

		delete scheduler;

		setup();
	}
}

#else

#include "Test_CircularBuffer.h"
#include "Test_LidarNavigation.h"

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Test::run();
}

#endif
