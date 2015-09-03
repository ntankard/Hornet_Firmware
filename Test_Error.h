#pragma once

#if BUILD_TYPE == FOR_TEST

#include <ArduinoUnit.h>
#include "Error.h"

test(Error_Regular)
{
	Error toTest;

	// test that its built corectly
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
	asm volatile("" ::: "memory");
	Error toTest;
	asm volatile("" ::: "memory");
	int postTest = -223;
	asm volatile("" ::: "memory");

	// check that the optomizer hasnt broken anything
	assertEqual((int)&postTest, (int)&toTest + sizeof(Error)+4);

	// test that its built corectly
	assertFalse(toTest.isError());

	// test that you can add error corectly
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

	// check that the error has not excaped its allocated memory
	assertEqual(postTest,-223);
}

#endif;
