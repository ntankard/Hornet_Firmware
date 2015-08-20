#pragma once
#include "Coms.h"
#include "CircularBuffer_Manager.h"
#include "Error.h"

class ComsEncoder
{
public:
	ComsEncoder(Coms* coms, Error *e);

	void run();

	void sendChar(uint8_t message);

	void sendRawAccGyro(float accel[3], float gyro[3]);

	void sendPitchRoll(float pitch, float roll);

	void sendLidarPoint(float angle, float distance);

	void sendLidarEOSweep(float pitch, float roll, float yaw);

private:
	Coms *_coms;
	Error *_e;


	uint8_t _messageBuffer[20];
	CircularBuffer_Manager<20> _messageBuffer_man;

	uint8_t _rawAccGyro[10][25];
	CircularBuffer_Manager<10> _rawAccGyro_man;

	uint8_t _pitchRoll[10][9];
	CircularBuffer_Manager<10> _pitchRoll_man;

	uint8_t _lidarData[10][9];
	CircularBuffer_Manager<10> _lidarData_man;
};

