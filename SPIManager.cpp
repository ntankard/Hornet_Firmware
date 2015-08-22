#include "SPIManager.h"


SPIManager::SPIManager()
{
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV16); // 1MHZ SPI rate
}