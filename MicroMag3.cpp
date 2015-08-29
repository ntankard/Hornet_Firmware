#include "MicroMag3.h"

#if ENABLE_MAG == ENABLED

#include <stdint.h>


#define X_ADDR 0b01100001
#define Y_ADDR 0b01100010
#define Z_ADDR 0b01100011

const uint8_t ADD[] = { X_ADDR, Y_ADDR, Z_ADDR };

MicroMag3::MicroMag3(SPIManager *theSPIManager, int SSNOTpin, int DRDYpin, int RESETpin)
{
	_SPIManager = theSPIManager;
	_SSNOTpin = SSNOTpin;
	_DRDYpin = DRDYpin;
	_RESETpin = RESETpin;

	pinMode(_SSNOTpin, OUTPUT);
	pinMode(_RESETpin, OUTPUT);
	pinMode(_DRDYpin, INPUT);
	digitalWrite(_SSNOTpin, LOW);
	digitalWrite(_RESETpin, LOW);

	_sensor = 0;
	_isMeasuring = false;
}

bool MicroMag3::init()
{
	sendCommand(ADD[_sensor]);
}

bool MicroMag3::update()
{
	//uint8_t data[2];
	if (digitalRead(_DRDYpin) == HIGH)
	{
		uint8_t byte_H, byte_L;
		//digitalWrite(_SSNOTpin, LOW);
		byte_H = _SPIManager->transfer(0);
		byte_L = _SPIManager->transfer(0);
		//digitalWrite(_SSNOTpin, HIGH);

		// read the data from the last measure
		//_SPIManager->read(_SSNOTpin, 0, data, 2);
		_lastValid[_sensor] = (byte_H << 8) | byte_L;

		_sensor++;
		if (_sensor >= 3)
		{
			_sensor = 0;
			Serial.println((String)_lastValid[0]);
		}

		// start a new measurment
		sendCommand(ADD[_sensor]);
	}
	return (_sensor == 0);
}

void MicroMag3::sendCommand(uint8_t command)
{
	//digitalWrite(_SSNOTpin, LOW);
	//delay(2);

	// pulse the reset
	//digitalWrite(_RESETpin, LOW);
	//delay(1);
	digitalWrite(_RESETpin, HIGH);
	//delay(1);
	digitalWrite(_RESETpin, LOW);
	//delay(2);

	//send the request
	//digitalWrite(_SSNOTpin, LOW);
	_SPIManager->transfer(command);
	//digitalWrite(_SSNOTpin, HIGH);
}

#endif
