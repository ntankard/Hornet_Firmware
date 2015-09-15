#pragma once

#if BUILD_TYPE == FOR_MANUAL_TEST

#include "Error.h"
#include "Magnetometer.h"
#include "MessageBuffer_Passer.h"
#include "Arduino.h"

void MTest_Magnetometer_Print()
{
	volatile Error _e;
	Magnetometer toTest(&_e);

	if (!toTest.start())
	{
		Serial.print("Failed to setup the mag");
		while (true){}
	}

	while (true)
	{
		if (toTest.run() != 0)
		{
			volatile MessageBuffer_Passer* data;
			data = toTest.getMessage();

			double z = data->getData()[0];

			z = z / 10000.0;

			z = degrees(z);

			Serial.println("Z:" + (String)(z));

			data = toTest.getMessage();
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void MTest_Magnetometer_RawPrint()
{
	volatile Error _e;
	Magnetometer toTest(&_e);

	if (!toTest.start())
	{
		Serial.print("Failed to setup the mag");
		while (true){}
	}

	while (true)
	{
		if (toTest.run() != 0)
		{
			volatile MessageBuffer_Passer* data;
			data = toTest.getMessage();
			data = toTest.getMessage();

			float x = data->getData()[0];
			float y = data->getData()[1];
			float z = data->getData()[2];

			float m = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

			//Serial.println("X:" + (String)(x/m)+" Y:" + (String)(y/m)+" Z:" + (String)(z/m));
			Serial.println("X:" + (String)(x ) + " Y:" + (String)(y ) + " Z:" + (String)(z));
			
		}
	}
}

#endif