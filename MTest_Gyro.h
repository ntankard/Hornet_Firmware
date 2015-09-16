#pragma once

#if BUILD_TYPE == FOR_MANUAL_TEST

#include "Gyro.h"
#include "MessageBuffer_Passer.h"
#include "Arduino.h"

void MTest_Gyro_Print()
{
	Gyro toTest;

	if (!toTest.start())
	{
		Serial.print("Failed to setup the acc");
		while (true){}
	}

	while (true)
	{
		if (toTest.run() != 0)
		{
			volatile MessageBuffer_Passer* data;
			data = toTest.getMessage();

			double x = data->getData()[0];
			double y = data->getData()[1];
			double z = data->getData()[2];

			x = x / 10000.0;
			y = y / 10000.0;
			z = z / 10000.0;

			x = degrees(x);
			y = degrees(y);
			z = degrees(z);

			Serial.println("X:" + (String)(x)+" Y:" + (String)(y)+" Y:" + (String)(z));
		}
	}
}

#endif