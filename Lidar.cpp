#include "Lidar.h"
#include "TimeOut.h"
#ifdef USE_LIDAR

Lidar::Lidar(volatile Error* e) :_lidarComs(e)
{
	_lastAngle = 0;
	_registerRead = 0;

}

//-----------------------------------------------------------------------------------------------------------------------------

bool Lidar::start()
{
	// Activate motor
	/*pinMode(C_LIDAR_MOTOCTL, OUTPUT);
	analogWrite(C_LIDAR_MOTOCTL, 255);*/

	// Reset
	_lidarComs.sendRequest(Reset);
	_lidarComs.run();

	//Empty buffer (extra data that was sent before the reset)
	delay(2000);
	while (C_LIDAR_SERIAL.available())
	{
		C_LIDAR_SERIAL.read();
	}

	// Check device health
	TimeOut timeOut;
	timeOut.start(1000);
	_lidarComs.sendRequest(Get_Health);
	while (true)
	{
		// wait for the return packet
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
	while (true)
	{
		// wait for the responce
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
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Lidar::run()
{
	// wait for a packet
	_lidarComs.run();
	if (_lidarComs.getIsDone())
	{
		DataPacket theData = _lidarComs.getLastDataPacket();

		double angle = ((theData.data.angle >> 1) / 64);
		double distance = ((theData.data.distance) / 4.0f);

		angle += LA_MOUNT_OFFSET;
		if (angle > 360)
		{
			angle = angle - 360;
		}

		// store for base stattion
		_lastLidarRegister.getData()[0] = angle * 90;
		_lastLidarRegister.getData()[1] = distance;

		if (distance > LA_MIN_RADIUS)
		{
			// process colision avoidance 
			_avoidance.newPoint(angle, distance);
			//_nav.processLidarData(angle, distance);
		}

		if (_lastAngle > 300 && angle < 20 && _lastAngle > angle)
		{
			_avoidance.endOfSweep();
			//_nav.EOSweep(0,0,0);
		}

		_lastAngle = angle;

		return true;
	}
	return false;
}

#endif