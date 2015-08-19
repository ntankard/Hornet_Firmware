#include "Hornet_Firmware_Test.h"
#include "Test_CircularBuffer.h"

#if BUILD_TYPE == FOR_TEST

void Hornet_Firmware_Test()
{
	Serial.begin(9600);
	Test** tests = new Test*[200];
	tests[0] = new Test_CircularBuffer();

	tests[0]->setup();
	Serial.print(tests[0]->run());
	tests[0]->cleanUp();
}

#endif