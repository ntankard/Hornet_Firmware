#pragma once
#include "CONFIG.h"

#if ENABLE_MAG == ENABLED
#include "SPIManager.h"
#include <stdint.h>

class MicroMag3
{
public:
	MicroMag3(SPIManager *theSPIManager, int SSNOTpin, int DRDYpin, int RESETpin);

	bool init();

	bool update();

	//get data
private:
	void sendCommand(uint8_t command);

	int _SSNOTpin;
	int _DRDYpin;
	int _RESETpin;
	SPIManager *_SPIManager;

	int _sensor;
	bool _isMeasuring;

	int16_t _lastValid[3];
};

#endif

