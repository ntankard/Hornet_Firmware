#pragma once
#include "Test.h"
#include <Arduino.h>


class Test_CircularBuffer :public Test
{
public:


	void setup();

	String run();

	void cleanUp();
};

