#pragma once

#if BUILD_TYPE == FOR_MANUAL_TEST

#include "Error.h"
#include "Lidar.h"

void MTest_Lidar_Print()
{
	volatile Error theError;
	Lidar theLidar(&theError);

	if (!theLidar.start())
	{
		Serial.println("LIDAR failed to start");
		LOCK;
	}
	Serial.println("LIDAR connection successful");


	while (true)
	{
		if (theLidar.run() != 0)
		{
			volatile MessageBuffer_Passer* data;
			data = theLidar.getMessage();

			double angle = data->getData()[0];
			double distance = data->getData()[1];

			angle = angle / 80.0;

			Serial.println("Angle:" + (String)(angle)+" Distance:" + (String)(distance));
		}
	}
}

#endif