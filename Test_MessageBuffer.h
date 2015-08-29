#pragma once

#if BUILD_TYPE == FOR_TEST

#include "MessageBuffer.h"

test(MessageBuffer_float)
{
	const int testSize = 4;
	const int typeSize = sizeof(float);
	const int testID = 23;

	// create the test data
	float inBuffer[] = { 23432.43234, -234.124, 242, 0 };
	uint8_t *outBuffer = reinterpret_cast<uint8_t *>(&inBuffer);

	MessageBuffer<testSize,1> toTest;
	toTest.setData(inBuffer);

	// check the real data
	for (int i = 0; i < testSize; i++)
	{
		assertEqual(inBuffer[i], toTest.getData()[i]);
	}

	// check the byte data
	for (int i = 0; i < (testSize*typeSize); i++)
	{
		assertEqual(outBuffer[i], toTest.getBytes()[i]);
	}

}

/*

test(MessageBuffer_double)
{
	const int testSize = 4;
	const int typeSize = sizeof(double);
	const int testID = 23;

	// create the test data
	double inBuffer[] = { 1234.234, -22534.23, 1432, 0 };
	uint8_t *outBuffer = reinterpret_cast<uint8_t *>(&inBuffer);

	MessageBuffer<double, testSize> toTest(testID);
	toTest.setMessage(inBuffer);

	// check the real data
	for (int i = 0; i < testSize; i++)
	{
		assertEqual(inBuffer[i], toTest.getMessage()[i]);
	}

	// check the byte data
	for (int i = 0; i < (testSize*typeSize); i++)
	{
		assertEqual(outBuffer[i], toTest.getBytes()[i]);
	}
}

test(MessageBuffer_int)
{
	const int testSize = 4;
	const int typeSize = sizeof(int);
	const int testID = 23;

	// create the test data
	int inBuffer[] = { 3453, -4324, 142, 0 };
	uint8_t *outBuffer = reinterpret_cast<uint8_t *>(&inBuffer);

	MessageBuffer<int, testSize> toTest(testID);
	toTest.setMessage(inBuffer);

	// check the real data
	for (int i = 0; i < testSize; i++)
	{
		assertEqual(inBuffer[i], toTest.getMessage()[i]);
	}

	// check the byte data
	for (int i = 0; i < (testSize*typeSize); i++)
	{
		assertEqual(outBuffer[i], toTest.getBytes()[i]);
	}
}

test(MessageBuffer_int16_t)
{
	const int testSize = 4;
	const int typeSize = sizeof(int16_t);
	const int testID = 23;

	// create the test data
	int16_t inBuffer[] = { 3425, -234, 12, 0 };
	uint8_t *outBuffer = reinterpret_cast<uint8_t *>(&inBuffer);

	MessageBuffer<int16_t, testSize> toTest(testID);
	toTest.setMessage(inBuffer);

	// check the real data
	for (int i = 0; i < testSize; i++)
	{
		assertEqual(inBuffer[i], toTest.getMessage()[i]);
	}

	// check the byte data
	for (int i = 0; i < (testSize*typeSize); i++)
	{
		assertEqual(outBuffer[i], toTest.getBytes()[i]);
	}
}
*/
#endif;
 