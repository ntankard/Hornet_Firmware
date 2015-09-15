#pragma once

#if BUILD_TYPE == FOR_TEST

#include "MessageBuffer_Manager.h"
#include "MessageBuffer.h"
#include "MessageBuffer_Passer.h"

test(MessageBuffer_Manager_Lock)
{
	const int MessageID = 4;
	const int MessageSize = 8;
	const int ToMonitor = 8;
	const uint8_t ComPri = 2;
	const int BufferSize = 5;

	MessageBuffer_Manager<MessageID, MessageSize, ToMonitor, ComPri, BufferSize> toTest;
	volatile MessageBuffer_Passer* removed;
	volatile MessageBuffer_Passer* removedLastValid;

	// check that you can get 5 lockable objects
	for (int i = 0; i < BufferSize; i++)
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
	const int MessageID = 4;
	const int MessageSize = 8;
	const int ToMonitor = 8;
	const uint8_t ComPri = 2;
	const int BufferSize = 5;

	MessageBuffer_Manager<MessageID, MessageSize, ToMonitor, ComPri, BufferSize> toTest;
	volatile MessageBuffer_Passer* removed;

	// get a buffer
	removed = toTest.getAvailable();
	assertFalse(removed->isLocked());

	// create test data
	for (int i = 0; i < MessageSize; i++)
	{
		removed->getData()[i] = (int16_t)random(-30000, 30000);
	}
	uint8_t *outBuffer = reinterpret_cast<uint8_t *>((int16_t*)removed->getData());
	assertEqual(removed->getDataSize(), MessageSize);

	// test the raw data
	for (int i = 0; i < MessageSize * sizeof(int16_t); i++)
	{
		assertEqual(outBuffer[i], removed->getBytes()[i]);
	}

	// test the packet
	assertEqual(MessageID, ((uint8_t*)removed->getPacket())[0]);
	for (int i = 0; i < MessageSize * sizeof(int16_t); i++)
	{
		assertEqual(outBuffer[i], removed->getPacket()[i + 1]);
	}
}

test(MessageBuffer_Manager_Data)
{
	const int MessageID = 4;
	const int MessageSize = 2;
	const int ToMonitor = 8;
	const uint8_t ComPri = 2;
	const int BufferSize = 5;

	MessageBuffer_Manager<MessageID, MessageSize, ToMonitor, ComPri, BufferSize> toTest;
	volatile MessageBuffer_Passer* removed;

	// generate the data
	int16_t inBuffer[BufferSize][MessageSize];
	for (int i = 0; i < BufferSize; i++)
	{
		for (int j = 0; j < MessageSize; j++)
		{
			inBuffer[i][j] = (int16_t)random(-30000, 30000);
		}
	}

	// check that the data is retaind properly
	for (int i = 0; i < BufferSize; i++)
	{
		removed = toTest.getAvailable();
		assertFalse(removed->isLocked());
		removed->copyData(inBuffer[i]);
		for (int j = 0; j < MessageSize; j++)
		{
			assertEqual(inBuffer[i][j], removed->getData()[j]);
		}
	}

	// check that data is maintained in a locked buffer
	removed = toTest.getAvailable();
	assertFalse(removed->isLocked());
	removed->copyData(inBuffer[0]);
	removed->lock();
	for (int j = 0; j < MessageSize; j++)
	{
		assertEqual(inBuffer[0][j], removed->getData()[j]);
	}

	volatile MessageBuffer_Passer* second = toTest.getAvailable();
	assertFalse(second->isLocked());
	second->copyData(inBuffer[1]);

	for (int j = 0; j < MessageSize; j++)
	{
		assertEqual(inBuffer[0][j], removed->getData()[j]);
	}
}

#endif;