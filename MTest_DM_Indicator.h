#pragma once

#include "Error.h"
#include "DM_Indicator.h"

void MTest_DM_Indicator_Points()
{
	Error e;
	Indicator toTest(&e);
	toTest.start();
	toTest.on();
	while (true)
	{
		for (int j = 0; j < (4 * 7); j++)
		{
			toTest.setDisplay(j, j, 0, 500);
			delay(50);
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void MTest_DM_Indicator_Safe()
{
	Error e;
	Indicator toTest(&e);
	toTest.start();
	toTest.on();
	while (true)
	{
		toTest.safeOn();
		for (int j = 0; j < (4 * 7); j++)
		{
			toTest.setDisplay(j, j, 0, 500);
			delay(50);
		}
		toTest.safeOff();
		for (int j = 0; j < (4 * 7); j++)
		{
			toTest.setDisplay(j, j, 0, 500);
			delay(50);
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void MTest_DM_Indicator_SafeWithBlink()
{
	Error e;
	Indicator toTest(&e);
	toTest.start();
	toTest.on();
	toTest.setDisplay(0, 10, 2, 250);
	toTest.safeOn();
	while (true)
	{
		toTest.run();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void MTest_DM_Indicator_FullSettings()
{
	Error e;
	Indicator toTest(&e);
	toTest.start();
	toTest.on();
	while (true)
	{
		for (int i = 0; i < (4 * 7); i++)
		{
			for (int j = 0; j < (4 * 7); j++)
			{
				toTest.setDisplay(i, j, 0, 500);
				delay(50);
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void MTest_DM_Indicator_SolidOn()
{
	Error e;
	Indicator toTest(&e);
	toTest.start();
	toTest.on();
	toTest.setDisplay(0, 10, 0, 500);

	while (true)
	{
		toTest.run();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void MTest_DM_Indicator_Blink()
{
	Error e;
	Indicator toTest(&e);
	toTest.start();
	toTest.on();
	toTest.setDisplay(0, 10, 1, 500);

	while (true)
	{
		toTest.run();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void MTest_DM_Indicator_Sequence()
{
	Error e;
	Indicator toTest(&e);
	toTest.start();
	toTest.on();
	toTest.setDisplay(0, 10, 2, 250);

	while (true)
	{
		toTest.run();
	}
}