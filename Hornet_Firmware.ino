// hardware libreys (do not remove)
#include <Wire.h>
#include <SPI.h>
//#include <ArduinoUnit.h>

#define FOR_HARDWARE 1
#define FOR_TEST 2

#define BUILD_TYPE FOR_HARDWARE

#if BUILD_TYPE == FOR_HARDWARE


// core
#include "HornetManager.h"
#include "Error.h"
#include "Scheduler.h"

//bus
#include "SPIManager.h"
#include "I2CManager.h"

//coms
#include "ComsDecoder.h"
#include "Coms.h"
	#include "Serial_Coms.h"
	#include "XBee_Coms.h"
#include "ComsEncoder.h"

#include "AccGyro.h"
#include "Indicator.h"
	#include "APM_Indicator.h"
	#include "DM_Indicator.h"
#include "Magnetometer.h"

#include "CONFIG.h"

int freeRam()
{
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

/*
void setup()
{

}

void loop()
{

}

Error error;
HornetManager manager(&error);
Scheduler scheduler(&error);

SPIManager spiManager(&error);
I2CManager i2cManager(&error);

ComsDecoder comsDecoder(&manager);
#if COM_MODE == COM_MODE_XBEE
XBee_Coms coms(&comsDecoder);
#endif
#if COM_MODE == COM_MODE_SERIAL
Serial_Coms coms(&comsDecoder);
#endif
ComsEncoder comsEncoder(&coms);*/



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
Indicator *indicator;


int i;

void setup()
{
	i = 0;
	delay(1000);
	Serial.begin(9600);	//@TODO this should be in the USB serial


	//Serial.clearWriteError();
	//Serial.flush();

	delay(2000);

	Serial.println("Start Build");
	Serial.println((String)freeRam());
	
	error = new Error();
	manager = new HornetManager(error);
	scheduler = new Scheduler(error);

	// construct the coms
			comsDecoder = new ComsDecoder(manager);
#if COM_MODE == COM_MODE_XBEE
	coms = new XBee_Coms(comsDecoder);
#endif
#if COM_MODE == COM_MODE_SERIAL
	coms = new Serial_Coms(comsDecoder);
#endif
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
				accGyro = new AccGyro(manager,error,spiManager,MPU6000_CS);
		#endif
		#ifdef USE_MPU6050
				accGyro = new AccGyro(manager, i2cManager, error);
		#endif
	#else
		accGyro = new AccGyro();
	#endif
	manager->attachAccGyro(accGyro);
	scheduler->addRunable(C_SCHEDULER_ACCGYRO_THREAD, accGyro);

	// construct the magnotomiter
	magnetometer = new Magnetometer(manager,spiManager,error);
	scheduler->addRunable(C_SCHEDULER_MAG_THREAD, magnetometer);
	manager->attachMagnetometer(magnetometer);

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
		indicator->safeOn();
		while (true){ Serial.println("FAILED TO START"); delay(1000); };
		//@TODO add error code here
	}

	if (!scheduler->startAll())
	{
		indicator->safeOn();
		while (true){ Serial.println("FAILED TO START 2"); delay(1000); };
		//@TODO add error code here
	}
	Serial.println((String)freeRam());
	Serial.println("End Build");

	manager->start();
}


void loop()
{
	manager->run();
	delay(1);

	/*if (!manager->run())
	{
		// periferal
		delete accGyro;
		delete magnetometer;
		delete indicator;

		// coms
		delete coms;
		delete comsDecoder;
		delete comsEncoder;

		//bus
		delete spiManager;
		delete i2cManager;

		//core
		delete manager;
		delete error;
		delete scheduler;

		setup();
	}
	delay(100);*/
}

#else

#include "Test_CircularBuffer.h"
#include "Test_CircularBuffer_Manager.h"
#include "Test_LidarNavigation.h"
#include "Test_MovingAverage.h"
#include "Test_TimeOut.h"
#include "Test_MessageBuffer.h"
#include "Test_MessageBuffer_Manager.h"

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Test::run();
}

#endif
