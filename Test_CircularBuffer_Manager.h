#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Error.h"
#include "CircularBuffer_Manager.h"

test(CircularBuffer_Manager_Setup)
{
	const int BufferSize = 100;
	Error e;
	CircularBuffer_Manager<BufferSize> _testBuffer(&e);

	// check to see that the buffer starts empty
	assertTrue(_testBuffer.isEmpty());
	assertFalse(_testBuffer.isFull());
	assertEqual(_testBuffer.size(), 0);
}

test(CircularBuffer_Manager_Size)
{
	const int BufferSize = 100;
	Error *e = new Error();
	CircularBuffer_Manager<BufferSize> _testBuffer(e);

	assertFalse(e->isError());

	// check to see that you can't remove from an empty buffer
	assertEqual(_testBuffer.remove(), 0);
	assertTrue(e->isError());
	delete e;
	e = new Error();

	// check to see that the buffer starts empty
	for (int i = 0; i < (BufferSize-1); i++)
	{
		assertEqual(_testBuffer.add(), i);
		assertFalse(_testBuffer.isEmpty());
		assertFalse(_testBuffer.isFull());
		assertEqual(_testBuffer.size(), i + 1);
	}

	assertFalse(e->isError());

	assertEqual(_testBuffer.add(), (BufferSize-1));
	assertFalse(_testBuffer.isEmpty());
	assertTrue(_testBuffer.isFull());
	assertEqual(_testBuffer.size(), BufferSize);

	// check that you get an error if you add too many
	assertEqual(_testBuffer.add(),0);
	assertTrue(e->isError());
}

test(CircularBuffer_Manager_Rotation)
{
	const int BufferSize = 100;
	const int ToAdd = 35;
	Error *e = new Error();
	CircularBuffer_Manager<BufferSize> _testBuffer(e);

	assertFalse(e->isError());

	// add 5 elements
	for (int i = 0; i < ToAdd; i++)
	{
		assertEqual(_testBuffer.add(),i);
		assertFalse(_testBuffer.isEmpty());
		assertFalse(_testBuffer.isFull());
		assertEqual(_testBuffer.size(), i + 1);
		assertFalse(e->isError());
	}

	// rotate the buffer and check that it behaves properly
	int addIndex = ToAdd;
	int removeIndex = 0;

	for (int i = 0; i < 100; i++)
	{
		assertFalse(_testBuffer.isEmpty());
		assertFalse(_testBuffer.isFull());
		assertEqual(_testBuffer.size(), ToAdd);

		assertEqual(_testBuffer.remove(), removeIndex);
		assertEqual(_testBuffer.add(), addIndex);

		addIndex++;
		if (addIndex == BufferSize)
		{
			addIndex = 0;
		}
		removeIndex++;
		if (removeIndex == BufferSize)
		{
			removeIndex = 0;
		}

	}
}


#endif