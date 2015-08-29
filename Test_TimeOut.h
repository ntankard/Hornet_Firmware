#pragma once

#if BUILD_TYPE == FOR_TEST

#include "TimeOut.h"

test(TimeOut_All)
{
	TimeOut toTest;

	// test initial setup
	assertTrue(toTest.hasTimeOut());

	// test inital start
	toTest.start(1000);
	assertFalse(toTest.hasTimeOut());

	// check that timeout dosnt ocur to early
	delay(500);
	assertFalse(toTest.hasTimeOut());

	// check that the timout dose ocure after the time
	delay(500);
	assertTrue(toTest.hasTimeOut());

	// check that the timout stay avtive
	delay(500);
	assertTrue(toTest.hasTimeOut());
}

#endif