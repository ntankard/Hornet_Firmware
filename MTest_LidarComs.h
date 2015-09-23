#pragma once

#if BUILD_TYPE == FOR_MANUAL_TEST

#include "Error.h"
#include "LidarComs.h"

void MTest_LidarComs_Print()
{
	volatile Error theError;
	LidarComs theLidarComs(&theError);

	theLidarComs.sendRequest(RPLIDAR_CMD_RESET);
	theLidarComs.run();

	delay(1000);
	while (C_LIDAR_SERIAL.available())
	{
		char t = C_LIDAR_SERIAL.read();

	}

	// set pin modes
	pinMode(C_LIDAR_MOTOCTL, OUTPUT);

	analogWrite(C_LIDAR_MOTOCTL, 255);

	theLidarComs.sendRequest(RPLIDAR_CMD_GET_DEVICE_HEALTH);

	while (true)
	{
		theLidarComs.run();
		if (theLidarComs.getIsDone())
		{
			HealthPacket theHealthPacket = theLidarComs.getLastHealthPacket();
			Serial.println((String)theHealthPacket.data.error_code);
			Serial.println((String)theHealthPacket.data.status);
			break;
		}
	}
	theLidarComs.sendRequest(RPLIDAR_CMD_SCAN);
	while (true)
	{
		theLidarComs.run();
		if (theLidarComs.getIsDone())
		{
			DataPacket test = theLidarComs.getLastDataPacket();

			float angle = ((test.data.angle >> 1) / 64);
			float distance = ((test.data.distance) / 4.0f);

			delay(4);


			if (angle > 0 && angle < 20)
			{
				Serial.println(distance);
			}
		}

	}
}

void MTest_LidarComs_PrintAll()
{
	volatile Error theError;
	LidarComs theLidarComs(&theError);

	theLidarComs.sendRequest(RPLIDAR_CMD_RESET);
	theLidarComs.run();

	delay(1000);
	while (C_LIDAR_SERIAL.available())
	{
		char t = C_LIDAR_SERIAL.read();

	}

	// set pin modes
	pinMode(C_LIDAR_MOTOCTL, OUTPUT);

	analogWrite(C_LIDAR_MOTOCTL, 255);

	theLidarComs.sendRequest(RPLIDAR_CMD_GET_DEVICE_HEALTH);

	while (true)
	{
		theLidarComs.run();
		if (theLidarComs.getIsDone())
		{
			HealthPacket theHealthPacket = theLidarComs.getLastHealthPacket();
			Serial.println((String)theHealthPacket.data.error_code);
			Serial.println((String)theHealthPacket.data.status);
			break;
		}
	}
	theLidarComs.sendRequest(RPLIDAR_CMD_SCAN);
	while (true)
	{
		theLidarComs.run();
		if (theLidarComs.getIsDone())
		{
			DataPacket test = theLidarComs.getLastDataPacket();

			float angle = ((test.data.angle >> 1) / 64);
			float distance = ((test.data.distance) / 4.0f);


				Serial.println("Angle:    " + (String)angle);
				Serial.println("Distance: " + (String)distance);
		}

	}
}

#endif