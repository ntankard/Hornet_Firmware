#pragma once

#include "CONFIG.h"

#ifdef USE_MPU6050

#include <stdint.h>

class AP_InertialSensor_MPU6050
{
public:
	AP_InertialSensor_MPU6050();

	void init();
	bool update();
	void get_gyros(float *);
	void get_accels(float *);

private :
	int MPU6050_read(int start, uint8_t *buffer, int size);
	int MPU6050_write(int start, const uint8_t *pData, int size);
	int MPU6050_write_reg(int reg, uint8_t data);
};

#endif

