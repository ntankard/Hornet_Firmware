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

#include "Arduino.h"
#include "PriorityManager.h"
#include "RollingcCorrelation.h"
#include "Point.h"

volatile Error e;
RollingCorrelation<10> _test(&e);

void setup()
{
	Serial.begin(115200);
	Serial.clearWriteError();
	Serial.flush();
	while (Serial.available() != 0)
	{
		Serial.read();
	}

	delay(3000);
}

int i = 0;

const float X[] = { 1721.019862,
1707.543678,
1695.306295,
1679.567909,
1661.579228,
1650.419053,
1637.000013,
1628.22092,
1617.206591,
1602.087272,
1589.951627,
1577.856949,
1569.79006,
1554.329668,
1541.420079,
1525.935839,
1510.825047,
1496.799594,
1478.674964,
1465.98037
};

const float Y[] = { 577.4120931,
614.6491916,
651.8299296,
689.2690989,
724.0930312,
763.5831312,
800.6299068,
839.7146154,
880.3570474,
915.6683142,
956.5218623,
996.1543289,
1039.021375,
1080.162545,
1119.907241,
1160.348575,
1201.764506,
1242.803775,
1284.685873,
1329.414365
};


void loop()
{
	Point toAdd;

	for (int i = 0; i < 10; i++)
	{
		toAdd.setPolar(X[i], Y[i]);
		_test.newPoint(toAdd);
	}
	while (true){};
}

#endif