#define FOR_HARDWARE 1
#define FOR_MANUAL_TEST 2
#define FOR_TEST 3
#define OTHER 4

#define BUILD_TYPE FOR_HARDWARE

#if BUILD_TYPE == FOR_HARDWARE

#include <Wire.h>
#include "Config.h"
#include "HornetManager.h"

HornetManager hornetManager;

void setup()
{

	Serial.begin(9600);	//@TODO this should be in the USB serial
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available())
	{
		Serial.read();
	}
	delay(500);
	Wire.begin();	// no idea why this needs to be here


	DEBUG_PRINT("Start Setup");

	hornetManager.start();

	DEBUG_PRINT("End Setup");
}

void loop()
{
	hornetManager.run();
}

#endif
#if BUILD_TYPE == FOR_TEST

#include <ArduinoUnit.h>

#include "Test_Scheduler.h"
#include "Test_Error.h"
#include "Test_SequenceGenerator.h"
#include "Test_CircularBuffer.h"
#include "Test_CircularBuffer_Manager.h"
#include "Test_MessageBuffer.h"
#include "Test_MessageBuffer_Manager.h"

void setup()
{
	Serial.begin(9600);
	delay(2000);
}

void loop()
{
	Test::run();
}

#endif
#if BUILD_TYPE == FOR_MANUAL_TEST

#include <Wire.h>

//#include "MTest_DM_Indicator.h"
#include "MTest_Gyro.h"

void setup()
{
	Serial.begin(9600);	//@TODO this should be in the USB serial
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available())
	{
		Serial.read();
	}
	delay(500);
	Wire.begin();	// no idea why this needs to be here

	//MTest_DM_Indicator_Points();
	//MTest_DM_Indicator_Safe();
	//MTest_DM_Indicator_SafeWithBlink();
	//MTest_DM_Indicator_FullSettings();
	//MTest_DM_Indicator_SolidOn();
	//MTest_DM_Indicator_Blink();
	//MTest_DM_Indicator_Sequence();

	MTest_Gyro_Print();
}

void loop()
{
}

#endif

#if BUILD_TYPE == OTHER


#endif