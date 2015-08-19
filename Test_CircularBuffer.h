#if BUILD_TYPE == FOR_TEST


test(CircularBuffer_Setup)
{
	Error e;
	CircularBuffer<int, 10> _testBuffer(&e);

	// check to see that the buffer starts empty
	assertTrue(_testBuffer.isEmpty());
	assertFalse(_testBuffer.isFull());
	assertEqual(_testBuffer.size(), 0);
}

test(CircularBuffer_Size)
{
	Error e;
	CircularBuffer<int, 10> _testBuffer(&e);

	// check to see that the buffer starts empty
	for (int i = 0; i < 9; i++)
	{
		_testBuffer.add(i);
		assertFalse(_testBuffer.isEmpty());
		assertFalse(_testBuffer.isFull());
		assertEqual(_testBuffer.size(), i + 1);
	}
	_testBuffer.add(10);
	assertFalse(_testBuffer.isEmpty());
	assertTrue(_testBuffer.isFull());
	assertEqual(_testBuffer.size(), 10);
}

/*
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
*/
#endif