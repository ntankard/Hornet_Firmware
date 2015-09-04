
#define FOR_HARDWARE 1
#define FOR_MANUAL_TEST 2
#define FOR_TEST 3

#define BUILD_TYPE FOR_HARDWARE

#if BUILD_TYPE == FOR_HARDWARE

#include "Config.h"
#include "Error.h"
#include "HornetManager.h"

Error e;
HornetManager hornetManager(&e);

void setup()
{
	Serial.begin(9600);	//@TODO this should be in the USB serial
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

#endif