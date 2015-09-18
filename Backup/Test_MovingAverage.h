#pragma once

#if BUILD_TYPE == FOR_TEST

#include "MovingAverage.h"

test(MovingAverage_Setup)
{
	Error _e;
	MovingAverage<float, 10> toTest(&_e);
	float testValue = 234.2543;
	// Check that the first itum is added corectly
	assertEqual(toTest.add(testValue), testValue);

	// Check to see that its filling up corectly
	for (int i = 0; i < 8; i++)
	{
		assertEqual((String)toTest.add(testValue), (String)testValue);	//@TODO explain/fix this
		//Serial.println((String)toTest.add(testValue));
		//Serial.println((String)(testValue));
	}

	// Check to see that the last value gets added corectly
	assertEqual(toTest.add(testValue), testValue);

	// Check to see that the average can work continuosly
	for (int i = 0; i < 100; i++)
	{
		assertEqual(toTest.add(testValue), testValue);
	}
}

#endif;

