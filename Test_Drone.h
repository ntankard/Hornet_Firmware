#pragma once

#if BUILD_TYPE == FOR_TEST

#include <ArduinoUnit.h>
#include "Drone.h"

#define ROLL ((settings->getData()[0] + settings->getData()[3]) - (settings->getData()[1] + settings->getData()[2]))
#define PITCH ((settings->getData()[2] + settings->getData()[3]) - (settings->getData()[0] + settings->getData()[1]))
#define YAW	((settings->getData()[1] + settings->getData()[3]) - (settings->getData()[0] + settings->getData()[2]))
#define THROTTLE ((settings->getData()[1] + settings->getData()[3]) + (settings->getData()[0] + settings->getData()[2]))

//-----------------------------------------------------------------------------------------------------------------------------

// WARNING WILL POWER THE ENGIENS
test(Drone_Setup)
{
	Drone toTest;
	volatile MessageBuffer_Passer* settings;

	// check this it starts up properly
	assertFalse(toTest.isArmed());

	// check that all motors are off
	settings = toTest.getCurrent();
	for (int i = 0; i < 4; i++)
	{
		assertEqual(settings->getData()[i], 0);
	}

	// try setting the throttel and check nothing happends
	toTest.newThrottle(50);

	// check this it starts up properly
	assertFalse(toTest.isArmed());

	// check that all motors are off
	settings = toTest.getCurrent();
	for (int i = 0; i < 4; i++)
	{
		assertEqual(settings->getData()[i], 0);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

// WARNING WILL POWER THE ENGIENS
test(Drone_Throttle)
{
	Drone toTest;
	volatile MessageBuffer_Passer* settings;
	
	toTest.arm();
	assertTrue(toTest.isArmed());

	for (int i = 0; i < 100; i++)
	{
		int throttle = (int16_t)random(1, 99);

		settings = toTest.newThrottle(throttle);
		for (int i = 0; i < 4; i++)
		{
			assertEqual(settings->getData()[i], throttle);
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

// WARNING WILL POWER THE ENGIENS
test(Drone_Roll)
{
	Drone toTest;
	volatile MessageBuffer_Passer* settings;

	toTest.arm();
	assertTrue(toTest.isArmed());
	settings = toTest.newThrottle(50);

	for (int i = 0; i < 100; i++)
	{
		int roll = (int16_t)random(1, 24)*4;
		settings = toTest.newPitchRoll(0,roll);
		assertEqual(ROLL, roll);
		assertEqual(THROTTLE, 200);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------

// WARNING WILL POWER THE ENGIENS
test(Drone_Pitch)
{
	Drone toTest;
	volatile MessageBuffer_Passer* settings;

	toTest.arm();
	assertTrue(toTest.isArmed());
	settings = toTest.newThrottle(50);

	for (int i = 0; i < 100; i++)
	{
		int pitch = (int16_t)random(1, 24) * 4;
		settings = toTest.newPitchRoll(pitch, 0);
		assertEqual(PITCH, pitch);
		assertEqual(THROTTLE, 200);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

// WARNING WILL POWER THE ENGIENS
test(Drone_Yaw)
{
	Drone toTest;
	volatile MessageBuffer_Passer* settings;

	toTest.arm();
	assertTrue(toTest.isArmed());
	settings = toTest.newThrottle(50);

	for (int i = 0; i < 100; i++)
	{
		int yaw = (int16_t)random(1, 24) * 4;
		settings = toTest.newYaw(yaw);
		assertEqual(YAW, yaw);
		assertEqual(THROTTLE, 200);
	}
}


//-----------------------------------------------------------------------------------------------------------------------------

// WARNING WILL POWER THE ENGIENS
test(Drone_Mixed)
{
	Drone toTest;
	volatile MessageBuffer_Passer* settings;

	toTest.arm();
	assertTrue(toTest.isArmed());
	settings = toTest.newThrottle(50);

	for (int i = 0; i < 100; i++)
	{
		int yaw = (int16_t)random(1, 15)*4;
		int pitch = (int16_t)random(1, 15)*4;
		int roll = (int16_t)random(1, 15)*4;
		toTest.newPitchRoll(pitch, roll);
		toTest.newYaw(yaw);
		assertEqual(YAW, yaw);
		assertEqual(PITCH, pitch);
		assertEqual(ROLL, roll);
		assertEqual(THROTTLE, 200);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

// WARNING WILL POWER THE ENGIENS
test(Drone_ToLow)
{
	Drone toTest;
	volatile MessageBuffer_Passer* settings;

	toTest.arm();
	assertTrue(toTest.isArmed());
	settings = toTest.newThrottle(20);

	for (int i = 0; i < 100; i++)
	{
		int yaw = (int16_t)random(-15, 15) * 4;
		int pitch = (int16_t)random(-15, 15) * 4;
		int roll = (int16_t)random(-15, 15) * 4;
		toTest.newPitchRoll(pitch, roll);
		toTest.newYaw(yaw);
		assertEqual(YAW, yaw);
		assertEqual(PITCH, pitch);
		assertEqual(ROLL, roll);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

// WARNING WILL POWER THE ENGIENS
test(Drone_ToHigh)
{
	Drone toTest;
	volatile MessageBuffer_Passer* settings;

	toTest.arm();
	assertTrue(toTest.isArmed());
	settings = toTest.newThrottle(80);

	for (int i = 0; i < 100; i++)
	{
		int yaw = (int16_t)random(1, 15) * 4;
		int pitch = (int16_t)random(1, 15) * 4;
		int roll = (int16_t)random(1, 15) * 4;
		toTest.newPitchRoll(pitch, roll);
		toTest.newYaw(yaw);
		assertEqual(YAW, yaw);
		assertEqual(PITCH, pitch);
		assertEqual(ROLL, roll);
	}
}

#endif