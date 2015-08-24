#include "AP_InertialSensor_MPU6050.h"

#ifdef USE_MPU6050

#include <Wire.h>

#define MPU6050_I2C_ADDRESS 0x68
#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_WHO_AM_I           0x75   // R

AP_InertialSensor_MPU6050::AP_InertialSensor_MPU6050()
{
}

void AP_InertialSensor_MPU6050::init()
{
	uint8_t c;
	Wire.begin();
	//@TODO add error check here
	MPU6050_read(MPU6050_WHO_AM_I, &c, 1);
	MPU6050_read(MPU6050_PWR_MGMT_1, &c, 1);
	MPU6050_write_reg(MPU6050_PWR_MGMT_1, 0);
}

int AP_InertialSensor_MPU6050::MPU6050_read(int start, uint8_t *buffer, int size)
{
	int i, n, error;

	Wire.beginTransmission(MPU6050_I2C_ADDRESS);
	n = Wire.write(start);
	if (n != 1)
		return (-10);

	n = Wire.endTransmission(false);    // hold the I2C-bus
	if (n != 0)
		return (n);

	// Third parameter is true: relase I2C-bus after data is read.
	Wire.requestFrom(MPU6050_I2C_ADDRESS, size, true);
	i = 0;
	while (Wire.available() && i<size)
	{
		buffer[i++] = Wire.read();
	}
	if (i != size)
		return (-11);

	return (0);  // return : no error
}

int AP_InertialSensor_MPU6050::MPU6050_write(int start, const uint8_t *pData, int size)
{
	int n, error;

	Wire.beginTransmission(MPU6050_I2C_ADDRESS);
	n = Wire.write(start);        // write the start address
	if (n != 1)
		return (-20);

	n = Wire.write(pData, size);  // write data bytes
	if (n != size)
		return (-21);

	error = Wire.endTransmission(true); // release the I2C-bus
	if (error != 0)
		return (error);

	return (0);         // return : no error
}

int AP_InertialSensor_MPU6050::MPU6050_write_reg(int reg, uint8_t data)
{
	int error;

	error = MPU6050_write(reg, &data, 1);

	return (error);
}

#endif
