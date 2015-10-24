#pragma once

#if BUILD_TYPE == FOR_TEST
/*
#include "MessageBuffer.h"

test(MessageBuffer_int16_t)
{
	const uint8_t ID = 4;
	const uint8_t ComPri = 6;
	const int Size = 16;

	// generate the test data
	int16_t inBuffer[Size];
	for (int i = 0; i < Size; i++)
	{
		inBuffer[i] = (int16_t)random(-30000, 30000);
	}
	uint8_t *outBuffer = reinterpret_cast<uint8_t *>(&inBuffer);

	MessageBuffer<ID, ComPri, Size> toTest;
	toTest.copyData(inBuffer);

	assertEqual(toTest.getID(), ID);

	// check the real data
	assertEqual(toTest.getDataSize(),Size);
	for (int i = 0; i < Size; i++)
	{
		assertEqual(inBuffer[i], toTest.getData()[i]);
	}


	// check the byte data
	assertEqual(toTest.getBytesSize(), (Size * sizeof(int16_t)));
	for (int i = 0; i < (Size * sizeof(int16_t)); i++)
	{
		assertEqual(outBuffer[i], toTest.getBytes()[i]);
	}

	// check the packet
	assertEqual(toTest.getPacketSize(), (Size * sizeof(int16_t)) + 1);
	for (int i = 0; i < (Size * sizeof(int16_t)); i++)
	{
		assertEqual(outBuffer[i], toTest.getPacket()[i +1]);
	}
}
*/
#endif;
 