#pragma once
#include "ComsEncoder.h"
#include "Error.h"

/**
 * \class	Monitor
 *
 * \brief	Monitors key values about the drone and ocasionaly notifys the base station
 *
 * \author	Nicholas
 * \date	1/08/2015
 */
class Monitor
{
public:

	/**
	 * \fn	Monitor::Monitor(ComsEncoder* theComsEncoder);
	 *
	 * \brief	Constructor.
	 * 			The monitor is off by default
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 *
	 * \param [in,out]	theComsEncoder	If non-null, the coms encoder.
	 */
	Monitor(ComsEncoder* theComsEncoder);

	/**
	 * \fn	void Monitor::on();
	 *
	 * \brief	Turn on base station notification
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 */
	void on();

	/**
	 * \fn	void Monitor::off();
	 *
	 * \brief	Turn off base station notification
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 */
	void off();

	/**
	 * \fn	void Monitor::newAccGyro(float accel[3], float gyro[3]);
	 *
	 * \brief	There are new AccGyro value avalible, notify the base station after _accRate new values
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 *
	 * \param	accel	The accel.
	 * \param	gyro 	The gyro.
	 */
	void newRawAccGyro(float accel[3], float gyro[3]);

	void newPitchRoll(float pitch, float roll);

	void newLidarPoint(float angle, float distance);

	void newLidarEOSweep(float pitch, float roll, float yaw);

private:

	/** \brief	The coms encoder. */
	ComsEncoder *_comsEncoder;

	/** \brief	The number of new acc events befor the base station is notifyed */
	int _rawAccRate;

	/** \brief	The number of acc events so far. */
	int _rawAccCount;

	/** \brief	Notify the base station? */
	bool _isOn;

	int _pitchRollRate;

	float _pitchRollCount;

	int _lidarDataRate;

	float _lidarDataCount;
};

