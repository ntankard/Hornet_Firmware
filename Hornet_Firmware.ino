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
#include "SPIManager.h"
#include "I2CManager.h"
#include "APM_Indicator.h"
#include "DM_Indicator.h"
#include "Magnetometer.h"

#include "CONFIG.h"

// core componenets
HornetManager *manager;
Error *error;
Scheduler *scheduler;

// bus
SPIManager *spiManager;
I2CManager *i2cManager;

// coms systems
Coms *coms;
ComsDecoder *comsDecoder;
ComsEncoder *comsEncoder;

// periferal systerms
AccGyro *accGyro;
Magnetometer *magnetometer;
Monitor *monitor;
Indicator *indicator;


void setup()
{
	Serial.begin(9600);	//@TODO this should be in the USB serial

	error = new Error();
	manager = new HornetManager(error);
	scheduler = new Scheduler(error);

	// construct the coms
	comsDecoder = new ComsDecoder(manager);
	coms = new Coms(comsDecoder);
		manager->attachComs(coms);
		scheduler->addRunable(C_SCHEDULER_COMS_THREAD, coms);
	comsEncoder = new ComsEncoder(coms, error);
		manager->attachComsEncoder(comsEncoder);
		scheduler->addRunable(C_SCHEDULER_COMENCODER_THREAD, comsEncoder);

	// set up conection infurstructor for the sensors
	spiManager = new SPIManager(error);
	i2cManager = new I2CManager(error);

	// construct the accselerator and gyro
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
	scheduler->addRunable(C_SCHEDULER_ACCGYRO_THREAD, accGyro);

	// construct the magnotomiter
	magnetometer = new Magnetometer(spiManager);
	scheduler->addRunable(C_SCHEDULER_MAG_THREAD, magnetometer);

	// construct the monitor
	monitor = new Monitor(comsEncoder);
	manager->attachMonitor(monitor);

	// construct the indicator
	#if ENABLE_INDICATOR == ENABLED
		#ifdef USE_APM_INDICATOR
			indicator = new APM_Indicator();
		#endif
		#ifdef USE_DM_INDICATOR
			indicator = new DM_Indicator();
		#endif
	#else
		indicator = new Indicator();
	#endif
	manager->attachIndicator(indicator);
	scheduler->addRunable(C_SCHEDULER_INDICATOR_THREAD, indicator);

	// attach the scedulor
	manager->attachScheduler(scheduler);

	// check build integrety
	if (scheduler->finish())
	{
		while (true){ Serial.println("FAILED TO START"); };
		//@TODO add error code here
	}

	//magnetometer->start();
	manager->start();
}

void loop()
{
	if (!manager->run())
	{

		// @TODO delete order should be backwards
		delete manager;
		delete error;
		delete scheduler;
		delete spiManager;
		delete i2cManager;
		delete coms;
		delete comsDecoder;
		delete comsEncoder;
		delete accGyro;
		delete magnetometer;
		delete monitor;
		delete indicator;
		delete scheduler;

		setup();
	}
}

#else

#include "Test_CircularBuffer.h"
#include "Test_LidarNavigation.h"
#include "Test_MovingAverage.h"

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Test::run();
}

#endif
