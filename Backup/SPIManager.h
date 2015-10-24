#pragma once
#include "SharedBusManager.h"

class SPIManager:public SharedBusManager
{
public:
	SPIManager(Error *theError);
	void read(uint8_t address, uint8_t start, uint8_t *buffer, int size);
	void write(uint8_t address, uint8_t start, uint8_t *buffer, int size);

	/**
	* \brief	Exposes the SPI.transfer fucntion
	*
	* \param	toSend	The data to send
	*
	* \return	The read data
	*/
	uint8_t transfer(uint8_t toSend);
};

