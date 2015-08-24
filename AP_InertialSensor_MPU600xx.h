#pragma once

#include "I2CManager.h"
#include "SPIManager.h"
#include "SharedBusManager.h"

class AP_InertialSensor_MPU600xx
{
public:
	AP_InertialSensor_MPU600xx(I2CManager *theI2CManager, uint8_t interruptPin);

	AP_InertialSensor_MPU600xx(SPIManager *theSPIManager, uint8_t cs_pin, uint8_t interruptPin);

	bool init();

	void getData();

	void update();

private:
	static void data_interrupt(void);

	void register_write(uint8_t reg, uint8_t val);
	uint8_t register_read(uint8_t reg);

	SharedBusManager *_sharedBusManager;

	uint8_t _address;
	uint8_t _interruptPin;
	bool _isSPI;

	int _readNum;
	uint8_t _data[14];

};

