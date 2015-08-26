#pragma once
#include "SharedBusManager.h"

class SPIManager:public SharedBusManager
{
public:
	SPIManager(Error *theError);
	void read(uint8_t address, uint8_t start, uint8_t *buffer, int size);
	void write(uint8_t address, uint8_t start, uint8_t *buffer, int size);
};

