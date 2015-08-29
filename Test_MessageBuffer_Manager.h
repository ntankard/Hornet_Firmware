#pragma once

#if BUILD_TYPE == FOR_TEST

#include "MessageBuffer_Manager.h"
#include "MessageBuffer.h"
#include "MessageBuffer_Passer.h"

test(MessageBuffer_Manager_Lock)
{
	const int MessageSize = 2;
	const int MessageID = 4;
	const int MessageBufferSize = 5;

	MessageBuffer_Manager<MessageSize, MessageID, MessageBufferSize> toTest;
	MessageBuffer_Passer* removed;
	MessageBuffer_Passer* removedLastValid;

	// check that you can get 5 lockable objects
	for (int i = 0; i < MessageBufferSize; i++)
	{
		removedLastValid = toTest.getAvailable();
		assertFalse(removedLastValid->isLocked());
		removedLastValid->lock();
	}

	// check that the last object cant be locked
	removed = toTest.getAvailable();
	assertTrue(removed->isLocked());

	// check that a new object cna be locked after one is unlocked
	removedLastValid->unlock();
	removed = toTest.getAvailable();
	assertFalse(removed->isLocked());

	// check that the system can be relocked
	removed->lock();
	removed = toTest.getAvailable();
	assertTrue(removed->isLocked());
}

test(MessageBuffer_Manager_Union)
{
	const int MessageSize = 4;
	const int MessageID = 4;
	const int MessageBufferSize = 5;

	MessageBuffer_Manager<MessageSize, MessageID, MessageBufferSize> toTest;
	MessageBuffer_Passer* removed;

	// get a buffer
	removed = toTest.getAvailable();
	assertFalse(removed->isLocked());

	// create test data
	float inBuffer[] = { 3425, -234, 12, 0 };
	uint8_t *outBuffer = reinterpret_cast<uint8_t *>(&inBuffer);
	removed->setData(inBuffer);
	assertEqual(removed->getSize(), MessageSize);

	// test the original data
	for (int i = 0; i < MessageSize; i++)
	{
		assertEqual(inBuffer[i], removed->getData()[i]);
	}

	// test the raw data
	for (int i = 0; i < MessageSize * sizeof(float); i++)
	{
		assertEqual(outBuffer[i], removed->getBytes()[i]);
	}

	// test the packet
	assertEqual(MessageID, removed->getPacket()[0]);
	for (int i = 0; i < MessageSize * sizeof(float); i++)
	{
		assertEqual(outBuffer[i], removed->getPacket()[i + 1]);
	}
}

test(MessageBuffer_Manager_Data)
{
	const int MessageSize = 2;
	const int MessageID = 4;
	const int MessageBufferSize = 5;

	MessageBuffer_Manager<MessageSize, MessageID, MessageBufferSize> toTest;
	MessageBuffer_Passer* removed;

	float inBuffer[MessageBufferSize][MessageSize] = { { 3425, -234 },
														{ 2343, -6556 },
														{ 0, 45 },
														{ -546, -908 },
														{ 345, 76 } };

	// check that the data is retaind properly
	for (int i = 0; i < MessageBufferSize; i++)
	{
		removed = toTest.getAvailable();
		assertFalse(removed->isLocked());
		removed->setData(inBuffer[i]);
		for (int j = 0; j < MessageSize; j++)
		{
			assertEqual(inBuffer[i][j], removed->getData()[j]);
		}
	}

	// check that data is maintained in a locked buffer
	removed = toTest.getAvailable();
	assertFalse(removed->isLocked());
	removed->setData(inBuffer[0]);
	removed->lock();
	for (int j = 0; j < MessageSize; j++)
	{
		assertEqual(inBuffer[0][j], removed->getData()[j]);
	}

	MessageBuffer_Passer* second = toTest.getAvailable();
	assertFalse(second->isLocked());
	second->setData(inBuffer[1]);

	for (int j = 0; j < MessageSize; j++)
	{
		assertEqual(inBuffer[0][j], removed->getData()[j]);
	}
}

#endif;