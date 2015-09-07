#pragma once
#include "Error.h"
//#include "SharedBusManager.h"

class I2CManager//:public SharedBusManager
{
public:
	I2CManager(volatile Error *theError);
	void read(uint8_t address, uint8_t start, uint8_t *buffer, int size);
	void write(uint8_t address, uint8_t start, uint8_t *buffer, int size);

	/**
	* \brief	Reads a single byte of data to a slave periferal device
	*
	* \param	address	The address of the periferial slave devce(chip selected line for SPI)
	* \param	reg		The address to read from
	*
	* \throw   E_BUS_FAIL    If the write fails
	*
	* \return The read data
	*/
	uint8_t read_reg(uint8_t address, uint8_t reg);

	/**
	* \brief	Writes a single byte of data to a slave periferal device
	*
	* \param	address	The address of the periferial slave devce(chip selected line for SPI)
	* \param	reg		The address to write to
	* \param	val		The data to write
	*
	* \throw   E_BUS_FAIL    If the write fails
	*/
	void write_reg(uint8_t address, uint8_t reg, uint8_t val);
private:
	volatile Error *_e;
};

