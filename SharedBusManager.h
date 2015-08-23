#pragma once
#include <stdint.h>
#include "Error.h"


/**
* \brief	A abstract object to represent a bus with slave devices (SPI and I2C for example)
*/
class SharedBusManager
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	theError	The shared error object
	* 
	* \author	Nicholas
	* \date	1/08/2015
	*/
	SharedBusManager(Error *theError){ _e = theError; }

	/**
	* \brief	Reads a sequence of bytes from a slave periferal device
	*
	* \param	address	The address of the periferial slave devce(chip selected line for SPI)
	* \param	start	The address to start reading from
	* \param	buffer	A place to dump the read data
	* \param	size	The number of bytes to read	
	* 					
	* \throw   E_BUS_FAIL    If the read fails
	*/
	virtual void read(uint8_t address, uint8_t start, uint8_t *buffer, int size) = 0;

	/**
	* \brief	Write a sequence of bytes to a slave periferal device
	*
	* \param	address	The address of the periferial slave devce(chip selected line for SPI)
	* \param	start	The address to start writing to
	* \param	buffer	The data to write
	* \param	size	The number of bytes to write
	*
	* \throw   E_BUS_FAIL    If the write fails
	*/
	virtual void write(uint8_t address, uint8_t start, uint8_t *buffer, int size) = 0;

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
	
protected:

	/** \brief	The shared error object (mimics exeptions in c++) */
	Error *_e;

};

