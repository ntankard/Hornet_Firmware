#include "I2CManager.h"
#include <Wire.h>

I2CManager::I2CManager(Error *theError) :SharedBusManager(theError)
{
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
		_e->add(E_BUS_FAIL, "I2C bus write failed");
		Wire.endTransmission(true);
		return;
	}
	
	// attempt to hold the I2C bus for continuouse transfer
	error = Wire.endTransmission();
	if (error != 0)
	{
		_e->add(E_BUS_FAIL, "I2C bus hold failed, Error code: "+(String)error);
		return;
	}

	Wire.beginTransmission(address);

	// read all the values
	if (Wire.requestFrom((uint8_t)address, (uint8_t)size, (uint8_t)true) != size)
	{
		_e->add(E_BUS_FAIL, "I2C bus read failed, not all the bytes were read ");
		while (true)
		{
			Serial.println("HELP IM ON FIRE");
		}
		return;
	}

	while (!Wire.available()){}

	// get the read values
	int i = 0;
	while (Wire.available() && i<size)
	{
		buffer[i++] = Wire.read();
	}
	if (i != size)
	{
		_e->add(E_BUS_FAIL, "I2C bus read failed, all bytes were read but could nt be received ");
	}


	error = Wire.endTransmission();
	if (error != 0)
	{
		_e->add(E_BUS_FAIL, "I2C bus hold failed, Error code: " + (String)error);
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
		_e->add(E_BUS_FAIL, "I2C bus write failed");
		//Wire.endTransmission(true);
		return;
	}

	// write the data
	if (Wire.write(buffer, size) != size)
	{
		_e->add(E_BUS_FAIL, "I2C bus write failed, not all bytes could be writen");
		//Wire.endTransmission(true);
		return;
	}

	// free the bus
	error = Wire.endTransmission(true);
	if (error != 0)
	{
		_e->add(E_BUS_FAIL, "I2C bus release failed, Error code: " + (String)error);
		return;
	}
}
