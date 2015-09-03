
#define FOR_HARDWARE 1
#define FOR_TEST 2

#define BUILD_TYPE FOR_TEST

#if BUILD_TYPE == FOR_HARDWARE

#include "Config.h"

void setup()
{
	Serial.begin(9600);	//@TODO this should be in the USB serial
	DEBUG_PRINT("Start Setup");

	DEBUG_PRINT("End Setup");
}

void loop()
{

}

#else

#include <ArduinoUnit.h>
#include "Test_Error.h"

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Test::run();
}

#endif
