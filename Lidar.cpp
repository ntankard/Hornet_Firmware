#include "Lidar.h"
#include "TimeOut.h"


Lidar::Lidar(volatile Error* e) :_lidarComs(e)
{
}

bool Lidar::start()
{
	// Activate motor
	/*pinMode(C_LIDAR_MOTOCTL, OUTPUT);
	analogWrite(C_LIDAR_MOTOCTL, 255);*/

	// Reset
	_lidarComs.sendRequest(Reset);
	TP("Rest");
	_lidarComs.run();

	//Empty buffer (extra data that was sent before the reset)
	delay(2000);
	while (C_LIDAR_SERIAL.available())
	{
		char t = C_LIDAR_SERIAL.read();

	}

	// Check device health
	TimeOut timeOut;
	timeOut.start(1000);
	_lidarComs.sendRequest(Get_Health);
	TP("Health");
	while (true)
	{
		_lidarComs.run();
		if (_lidarComs.getIsDone())
		{
			HealthPacket theHealthPacket = _lidarComs.getLastHealthPacket();
			DEBUG_PRINTLN("LIDAR Error Code: " + (String)theHealthPacket.data.error_code);
			DEBUG_PRINTLN("LIDAR Status:     " + (String)theHealthPacket.data.status);
			if (theHealthPacket.data.error_code != 0 || theHealthPacket.data.status != 0)
			{
				//analogWrite(C_LIDAR_MOTOCTL, 0);
				return false;
			}

			break;
		}
		if (timeOut.hasTimeOut())
		{
			//analogWrite(C_LIDAR_MOTOCTL, 0);
			return false;
		}
	}

	// Check device info
	timeOut.start(1000);
	_lidarComs.sendRequest(Get_Info);
	TP("Info");
	while (true)
	{
		_lidarComs.run();
		if (_lidarComs.getIsDone())
		{
			InfoPacket theInfoPacket = _lidarComs.getLastInfoPacket();
			DEBUG_PRINTLN("LIDAR Firmware Version: " + (String)theInfoPacket.data.firmware_version);
			DEBUG_PRINTLN("LIDAR Hardware Version: " + (String)theInfoPacket.data.hardware_version);
			DEBUG_PRINTLN("LIDAR Model:            " + (String)theInfoPacket.data.model);
			if (theInfoPacket.data.firmware_version != 1 || theInfoPacket.data.hardware_version != 206 || theInfoPacket.data.model != 0)
			{
				//analogWrite(C_LIDAR_MOTOCTL, 0);
				return false;
			}
			break;
		}
		if (timeOut.hasTimeOut())
		{
			//analogWrite(C_LIDAR_MOTOCTL, 0);
			return false;
		}
	}
	// Lidar checks completed, start scan
	_lidarComs.sendRequest(Scan);
	TP("Start");
	return true;
}


bool Lidar::run()
{
		
	_lidarComs.run();
	if (_lidarComs.getIsDone())
	{
		DataPacket theData = _lidarComs.getLastDataPacket();

		float angle = ((theData.data.angle >> 1) / 64);
		float distance = ((theData.data.distance) / 4.0f);

		TP((String)angle);

		/*_toSend = _lidarSender.getAvailable();
		_toSend->getData()[0] = angle * 80;
		_toSend->getData()[1] = distance;*/
		return true;
	}
	return false;
}

