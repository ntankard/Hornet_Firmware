#include "SharedBusManager.h"

SharedBusManager::SharedBusManager(Error *theError)
{ 
	_e = theError; 
}

//-----------------------------------------------------------------------------------------------------------------------------

void SharedBusManager::write_reg(uint8_t address, uint8_t reg, uint8_t val)
{
	write(address, reg, &val, 1);
}

//-----------------------------------------------------------------------------------------------------------------------------

uint8_t SharedBusManager::read_reg(uint8_t address, uint8_t reg)
{
	uint8_t buffer;
	read(address, reg, &buffer, 1);
	return buffer;
}