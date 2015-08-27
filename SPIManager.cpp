#include "SPIManager.h"
#include <SPI.h>

SPIManager::SPIManager(Error *theError) :SharedBusManager(theError)
{
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV16); // 1MHZ SPI rate

	//@TODO remove this after the baromiter driver is added
	pinMode(40, OUTPUT);
	digitalWrite(40, HIGH);
}

//-----------------------------------------------------------------------------------------------------------------------------

void SPIManager::read(uint8_t address, uint8_t start, uint8_t *buffer, int size)
{
	digitalWrite(address, LOW);

	SPI.transfer(start);

	for (int i = 0; i < size; i++)
	{
		buffer[i] = SPI.transfer(0);
	}

	digitalWrite(address, HIGH);
}

//-----------------------------------------------------------------------------------------------------------------------------

void SPIManager::write(uint8_t address, uint8_t start, uint8_t *buffer, int size)
{
	digitalWrite(address, LOW);

	SPI.transfer(start);

	for (int i = 0; i < size; i++)
	{
		SPI.transfer(buffer[i]);
	}

	digitalWrite(address, HIGH);
}