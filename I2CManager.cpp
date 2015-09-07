#include "I2CManager.h"
#include <Wire.h>
#include "TimeOut.h"

I2CManager::I2CManager(volatile Error *theError) //:SharedBusManager(theError)
{
	_e = theError;
	Wire.begin();
}

//-----------------------------------------------------------------------------------------------------------------------------

void I2CManager::read(uint8_t address, uint8_t start, uint8_t *buffer, int size)
{
	int  error;
	Wire.beginTransmission(address);

	// set the read address
	if (Wire.write(start) != 1)
	{
		_e->add(E_BUS_FAIL, __LINE__);
		Wire.endTransmission(true);
		return;
	}
	
	// attempt to hold the I2C bus for continuouse transfer
	error = Wire.endTransmission();
	if (error != 0)
	{
		_e->add(E_BUS_FAIL, __LINE__);
		return;
	}

	Wire.beginTransmission(address);

	// read all the values
	if (Wire.requestFrom((uint8_t)address, (uint8_t)size, (uint8_t)true) != size)
	{
		_e->add(E_BUS_FAIL, __LINE__);
		return;
	}

	// wait for the first peice of slave data
	TimeOut readWait;
	readWait.start(C_I2C_READ_WAIT);
	while (!Wire.available())
	{
		if (readWait.hasTimeOut())
		{
			_e->add(E_BUS_FAIL, __LINE__);
		}
	}

	// get the read values
	int i = 0;
	while (Wire.available() && i<size)
	{
		buffer[i++] = Wire.read();
	}
	if (i != size)
	{
		_e->add(E_BUS_FAIL, __LINE__);
	}


	error = Wire.endTransmission();
	if (error != 0)
	{
		_e->add(E_BUS_FAIL, __LINE__);
		return;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void I2CManager::write(uint8_t address, uint8_t start, uint8_t *buffer, int size)
{
	int error;
	Wire.flush();
	Wire.clearWriteError();
	Wire.beginTransmission(address);

	// set the write address
	if (Wire.write(start) != 1)
	{
		_e->add(E_BUS_FAIL, __LINE__);
		//Wire.endTransmission(true);
		return;
	}

	// write the data
	if (Wire.write(buffer, size) != size)
	{
		_e->add(E_BUS_FAIL, __LINE__);
		//Wire.endTransmission(true);
		return;
	}

	// free the bus
	error = Wire.endTransmission(true);
	if (error != 0)
	{
		_e->add(E_BUS_FAIL, __LINE__);
		return;
	}


}

//-----------------------------------------------------------------------------------------------------------------------------

void I2CManager::write_reg(uint8_t address, uint8_t reg, uint8_t val)
{
	write(address, reg, &val, 1);
}

//-----------------------------------------------------------------------------------------------------------------------------

uint8_t I2CManager::read_reg(uint8_t address, uint8_t reg)
{
	uint8_t buffer;
	read(address, reg, &buffer, 1);
	return buffer;
}
