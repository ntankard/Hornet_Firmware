#pragma once

#if BUILD_TYPE == FOR_TEST

#include "MessageBuffer.h"

test(MessageBuffer_float)
{
	const uint8_t ID = 4;
	const uint8_t ComPri = 6;
	const int Size = 16;

	// generate the test data
	float inBuffer[Size];
	for (int i = 0; i < Size; i++)
	{
		inBuffer[i] = (float)random(-10000, 10000) * 0.0001;
	}
	uint8_t *outBuffer = reinterpret_cast<uint8_t *>(&inBuffer);

	MessageBuffer<ID, ComPri, Size> toTest;
	toTest.copyData(inBuffer);

	// check the real data
	assertEqual(toTest.getDataSize(),Size);
	for (int i = 0; i < Size; i++)
	{
		assertEqual(inBuffer[i], toTest.getData()[i]);
	}

	// check the byte data
	assertEqual(toTest.getBytesSize(), (Size * sizeof(float)));
	for (int i = 0; i < (Size * sizeof(float)); i++)
	{
		assertEqual(outBuffer[i], toTest.getBytes()[i]);
	}

	// check the packet
	assertEqual(toTest.getPacketSize(), (Size * sizeof(float))+1);
	for (int i = 0; i < (Size * sizeof(float)); i++)
	{
		assertEqual(outBuffer[i], toTest.getPacket()[i + 1]);
	}
}

#endif;
 