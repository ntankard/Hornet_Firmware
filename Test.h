#pragma once
#include <Arduino.h>



class Test
{
public:

	virtual void setup() = 0;

	virtual String run() = 0;

	virtual void cleanUp() = 0;
};

