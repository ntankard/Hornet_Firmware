#if BUILD_TYPE == FOR_TEST

#pragma once
#include "Test.h"
#include <Arduino.h>
#include "CircularBuffer.h"


class Test_CircularBuffer :public Test
{
public:


	void setup();

	String run();

	void cleanUp();

private:
	CircularBuffer<int, 10> *_testBuffer;
};

#endif