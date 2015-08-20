#include "Lidar.h"
#include "CONFIG.h"

Lidar::Lidar(HornetManager* theManager)
{
	_hornetManager = theManager;
}

void Lidar::start()
{
#ifdef USE_LIDAR
	_lidar.begin(C_LIDAR_SERIAL);
	pinMode(C_LIDAR_MOTOCTL, OUTPUT);

	analogWrite(C_LIDAR_MOTOCTL, 0); //stop the rplidar motor

	// try to detect RPLIDAR... 
	rplidar_response_device_info_t info;
	if (IS_OK(_lidar.getDeviceInfo(info, 100))) {
		// detected...
		_lidar.startScan();

		// start motor rotating at max allowed speed
		analogWrite(C_LIDAR_MOTOCTL, 255);
	}
	else
	{
		//@TODO add throw here
	}
#endif
}

void Lidar::run()
{
#ifdef USE_LIDAR
	if (IS_OK(_lidar.waitPoint())) {
		float distance = _lidar.getCurrentPoint().distance; //distance value in mm unit
		float angle = _lidar.getCurrentPoint().angle; //angle value in degree
		bool  startBit = _lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
		byte  quality = _lidar.getCurrentPoint().quality; //quality of the current measurement

		//@TODO add notification
		if (startBit)
		{
			// Notify sweep complete
			_hornetManager->ND_LidarPoint(angle, distance);
			_hornetManager->ND_LidarEOSweep(0, 0, 0); //@TODO add data
		}
		else
		{
			// Notify normal point
			_hornetManager->ND_LidarPoint(angle, distance);
		}
	}
#endif
}