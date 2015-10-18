
#define FOR_HARDWARE 1
#define FOR_MANUAL_TEST 2
#define FOR_TEST 3
#define OTHER 4

#define BUILD_TYPE FOR_HARDWARE

#if BUILD_TYPE == FOR_HARDWARE

#include <Wire.h>
#include <Servo.h>
#include "Config.h"
#include "HornetManager.h"

HornetManager hornetManager;

void setup()
{
	delay(1000);
	Serial.begin(9600);	//@TODO this should be in the USB serial
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available()!=0)
	{
		Serial.read();
	}
	delay(1000);
	while (Serial.available()!=0)
	{
		Serial.read();
	}
#if COM_MODE == XBEE
	C_XBEE_COMS_PORT.begin(9600);	//@TODO this should be in the USB serial
	C_XBEE_COMS_PORT.clearWriteError();
	C_XBEE_COMS_PORT.flush();
	while (C_XBEE_COMS_PORT.available())
	{
		C_XBEE_COMS_PORT.read();
	}
#endif

	delay(500);
	Wire.begin();	// no idea why this needs to be here

	//TP((String)Serial.available());
	Serial.println(F("Start Setup"));

	hornetManager.start();

	Serial.println(F("End Setup"));
}

int a = 0;

void loop()
{
	a++;
	//hornetManager.run();
	//TP((String)a);
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

// will affect the hardware!!
#include "Test_Drone.h"

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

#include <Arduino.h>
#include "Coms.h"

Coms toTest;

void setup()
{
	Serial.begin(9600);	//@TODO this should be in the USB serial
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available())
	{
		Serial.read();
	}
}

int i = 0;

void loop()
{
	toTest.run();
}

#endif