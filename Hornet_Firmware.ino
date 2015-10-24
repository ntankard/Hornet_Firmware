#define FOR_HARDWARE 1
#define FOR_MANUAL_TEST 2
#define FOR_TEST 3
#define OTHER 4

#define BUILD_TYPE FOR_TEST

#if BUILD_TYPE == FOR_HARDWARE

#include <Wire.h>
#include <Servo.h>
#include "Config.h"
#include "HornetManager.h"

HornetManager hornetManager;

void setup()
{
	// turn on one of the pins to act as a refrence for a logic converter to the XBee
	pinMode(38, OUTPUT);
	digitalWrite(38, HIGH);

	// setup debug serial (also primary coms if XBee is off)
	Serial.begin(115200);
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available()!=0)
	{
		Serial.read();
	}

	// setup XBee coms
#if COM_MODE == XBEE
	XBEE_SERIAL.begin(115200);
	XBEE_SERIAL.clearWriteError();
	XBEE_SERIAL.flush();
	while (XBEE_SERIAL.available())
	{
		XBEE_SERIAL.read();
	}
#endif

	// setup LIDAR coms
#ifdef USE_LIDAR
	C_LIDAR_SERIAL.begin(115200);	//@TODO this should be in the USB serial
	C_LIDAR_SERIAL.clearWriteError();
	C_LIDAR_SERIAL.flush();
	while (C_LIDAR_SERIAL.available())
	{
		C_LIDAR_SERIAL.read();
	}
#endif

	// setupd I2C coms for accseleromiter
	delay(500);
	Wire.begin();	

	Serial.println(F("Start Setup"));

	hornetManager.start();

	Serial.println(F("End Setup"));
}

//-----------------------------------------------------------------------------------------------------------------------------

void loop()
{
	hornetManager.run();
}

#endif
#if BUILD_TYPE == FOR_TEST

#include <ArduinoUnit.h>

#include "Test_MessageBuffer.h"
#include "Test_SequenceGenerator.h"
#include "Test_CircularBuffer.h"
#include "Test_CircularBuffer_Manager.h"
#include "Test_Error.h"
#include "Test_Scheduler.h" 


#include "Test_Point.h"
#include "Test_Anchor.h"
#include "Test_AnchorManager.h"
#include "Test_DoublyLinkedNodeIterator.h"
#include "Test_Feature.h"
#include "Test_FeatureManager.h"
#include "Test_Pattern.h"
#include "Test_PatternManager.h"
#include "Test_Point.h"
#include "Test_PointManager.h"


void setup()
{
	Serial.begin(115200);
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available() != 0)
	{
		Serial.read();
	}

	delay(4000);
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