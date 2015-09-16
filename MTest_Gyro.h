#pragma once

#if BUILD_TYPE == FOR_MANUAL_TEST

#include "Gyro.h"
#include "MessageBuffer_Passer.h"
#include "Arduino.h"

void MTest_Gyro_Print()
{
	//volatile Error _e;
	Gyro toTest;

	if (!toTest.start())
	{
		Serial.print("Failed to setup the acc");
		while (true){}
	}
	//Serial.print("YES");

	while (true)
	{
		//delay(100);
		toTest.run();
		//delay(50);

		/*if (toTest.run() != 0)
		{
			volatile MessageBuffer_Passer* data;
			data = toTest.getMessage();

			double x = data->getData()[0];
			double y = data->getData()[1];

			x = x / 10000.0;
			y = y / 10000.0;

			x = degrees(x);
			y = degrees(y);

			Serial.println("X:" + (String)(x)+" Y:" + (String)(y));

			data = toTest.getMessage();
		}*/
	}
}

#endif