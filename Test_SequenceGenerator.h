#pragma once

#if BUILD_TYPE == FOR_TEST

#include <ArduinoUnit.h>
#include "SequenceGenerator.h"

test(SequenceGenerator_On)
{
	SequenceGenerator toTest;

	// test that is starts right
	assertTrue(toTest.isHigh());

	toTest.set(0, 0, 100);
	assertTrue(toTest.isHigh());
	// test that it always stays high
	for (int i = 0; i < 100; i++)
	{
		assertFalse(toTest.run());
		assertTrue(toTest.isHigh());
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

test(SequenceGenerator_Blink)
{
	SequenceGenerator toTest;

	// test that is starts right
	assertTrue(toTest.isHigh());

	toTest.set(0, 1, 20);

	// test that it always stays high
	for (int i = 0; i < 250; i++)
	{
		delay(2);
		assertTrue(toTest.run());
		assertTrue(toTest.isHigh());
		delay(2);
		assertTrue(toTest.run());
		assertFalse(toTest.isHigh());

	}
}

//-----------------------------------------------------------------------------------------------------------------------------

test(SequenceGenerator_Sequence)
{
	SequenceGenerator toTest;
	int blinks;
	int gap;

	blinks = 8;
	gap = 5;
	toTest.set(0, blinks, gap);

	for (int k = 0; k < 5; k++){

		blinks = random(2, 10);
		gap = random(2, 10);
		toTest.set(0, blinks, gap);

		for (int i = 0; i < 5; i++)
		{
			// main pulse
			for (int i = 0; i < (blinks); i++)
			{
				delay(2);
				assertTrue(toTest.run());
				assertTrue(toTest.isHigh());
				delay(2);
				assertTrue(toTest.run());
				assertFalse(toTest.isHigh());
			}

			// gap
			for (int i = 0; i < ((gap * 2)); i++)
			{
				delay(2);
				assertFalse(toTest.run());
				assertFalse(toTest.isHigh());
			}
		}
	}
}

#endif;
