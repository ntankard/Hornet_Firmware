#pragma once

#include "I2CManager.h"
#include "SPIManager.h"
#include "SharedBusManager.h"

typedef union accel_t_gyro_union
{
	struct
	{
		uint8_t x_accel_h;
		uint8_t x_accel_l;
		uint8_t y_accel_h;
		uint8_t y_accel_l;
		uint8_t z_accel_h;
		uint8_t z_accel_l;
		uint8_t t_h;
		uint8_t t_l;
		uint8_t x_gyro_h;
		uint8_t x_gyro_l;
		uint8_t y_gyro_h;
		uint8_t y_gyro_l;
		uint8_t z_gyro_h;
		uint8_t z_gyro_l;
	} reg;
	struct
	{
		int16_t x_accel;
		int16_t y_accel;
		int16_t z_accel;
		int16_t temperature;
		int16_t x_gyro;
		int16_t y_gyro;
		int16_t z_gyro;
	} value;
};

class AP_InertialSensor_MPU600xx
{
public:
	AP_InertialSensor_MPU600xx(I2CManager *theI2CManager, uint8_t interruptPin);

	AP_InertialSensor_MPU600xx(SPIManager *theSPIManager, uint8_t cs_pin, uint8_t interruptPin);

	bool init();

	void getData();

	bool update();

	void get_gyros(float* gyro);
	void get_accels(float* accel);

private:
	static void data_interrupt(void);

	void register_write(uint8_t reg, uint8_t val);
	uint8_t register_read(uint8_t reg);

	SharedBusManager *_sharedBusManager;

	uint8_t _address;
	uint8_t _interruptPin;
	bool _isSPI;

	// interupt memory
	int _readNum;
	accel_t_gyro_union _data;

	// solid memory
	accel_t_gyro_union _safeData;
	int _missedReadings;

};

