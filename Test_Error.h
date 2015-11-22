#pragma once

#if BUILD_TYPE == FOR_TEST

#include <ArduinoUnit.h>
#include "Error.h"

test(Error_Regular)
{
	Error toTest;

	// test that it's built corectly
	assertFalse(toTest.isError());

	// test that you can add error corectly
	for (uint8_t i = 0; i < C_ERROR_BUFFER; i++)
	{
		toTest.add(i, 0);
		assertTrue(toTest.isError());
	}

	// test that all the errors were stored
	for (int i = (C_ERROR_BUFFER-1); i >= 0; i--)
	{
		assertTrue(toTest.isError());
		assertEqual(toTest.getError(), i << 8);
	}

	// check that all errors were removed
	assertFalse(toTest.isError());
}

test(Error_Overflow)
{
	Error toTest;

	// test that its built corectly
	assertFalse(toTest.isError());

	// test that you can add error correctly
	for (uint8_t i = 0; i < (C_ERROR_BUFFER * 2); i++)
	{
		toTest.add(i, 0);
		assertTrue(toTest.isError());
	}

	// test that all the errors were stored except the overflows
	for (int i = (C_ERROR_BUFFER - 1); i >= 0; i--)
	{
		assertTrue(toTest.isError());
		assertEqual(toTest.getError(), i << 8);
	}

	// check that all errors were removed properly
	assertFalse(toTest.isError());
}

#endif;
