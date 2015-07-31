#pragma once
#include "Coms.h"
#include "CircularBuffer_Manager.h"
#include "Error.h"

class ComsEncoder
{
public:
	ComsEncoder(Coms* coms, Error *e);

	void run();

	void sendAccGyro(float accel[3], float gyro[3]);

private:
	Coms *_coms;
	Error *_e;

	uint8_t _accGyro[10][25];
	CircularBuffer_Manager<10> _accGyro_man;
};

