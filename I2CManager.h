#pragma once
#include "SharedBusManager.h"

class I2CManager:public SharedBusManager
{
public:
	I2CManager(Error *theError);
	void read(uint8_t address, uint8_t start, uint8_t *buffer, int size);
	void write(uint8_t address, uint8_t start, uint8_t *buffer, int size);

};

