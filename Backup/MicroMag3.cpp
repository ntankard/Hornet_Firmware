#include "MicroMag3.h"

#if ENABLE_MAG == ENABLED

// register map
#define X_ADDR 0b01100001
#define Y_ADDR 0b01100010
#define Z_ADDR 0b01100011
const uint8_t ADD[] = { X_ADDR, Y_ADDR, Z_ADDR };

//-----------------------------------------------------------------------------------------------------------------------------

MicroMag3::MicroMag3(SPIManager *theSPIManager,Error *e)
{
	_SPIManager = theSPIManager;
	_e = e;

	pinMode(C_MAG_SSNOT, OUTPUT);
	pinMode(C_MAG_RESET, OUTPUT);
	pinMode(C_MAG_DRDY, INPUT);
	digitalWrite(C_MAG_SSNOT, LOW);	// this permidantly locks the SPI bus, remove if shared
	digitalWrite(C_MAG_RESET, LOW);

	_sensor = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool MicroMag3::init()
{
	TimeOut setupTime;

	// atempt to read
	sendCommand(ADD[_sensor]);

	// wait for the message
	setupTime.start(1000);
	while (digitalRead(C_MAG_DRDY) == LOW)
	{
		if (setupTime.hasTimeOut())
		{
			return false;
		}
	}

	// check the validity of the data
	uint8_t byte_H, byte_L;
	byte_H = _SPIManager->transfer(0);
	byte_L = _SPIManager->transfer(0);
	if (byte_H == 0 && byte_L == 0)
	{
		return false;
	}

	// start the next read
	sendCommand(ADD[_sensor]);
	_lastRead.start(C_MAG_MAX_READ_TIME);
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool MicroMag3::update()
{
	//uint8_t data[2];
	if (digitalRead(C_MAG_DRDY) == HIGH)
	{
		uint8_t byte_H, byte_L;
		byte_H = _SPIManager->transfer(0);
		byte_L = _SPIManager->transfer(0);

		// read the data from the last measure
		_lastValid[_sensor] = (byte_H << 8) | byte_L;

		_sensor++;
		if (_sensor >= 3)
		{
			_sensor = 0;

		}

		// start a new measurment
		sendCommand(ADD[_sensor]);
		_lastRead.start(C_MAG_MAX_READ_TIME);
	}
	else
	{
		if (_lastRead.hasTimeOut())
		{
			_e->add(E_HARDWARE_FAILURE, "Magnetometer Read failed (timeout)");
		}
	}

	return (_sensor == 0);
}

//-----------------------------------------------------------------------------------------------------------------------------

void MicroMag3::getData(int16_t *data)
{
	data[0] = _lastValid[0];
	data[1] = _lastValid[1];
	data[2] = _lastValid[2];
}

//-----------------------------------------------------------------------------------------------------------------------------

void MicroMag3::sendCommand(uint8_t command)
{
	digitalWrite(C_MAG_RESET, HIGH);
	//delay(1);
	digitalWrite(C_MAG_RESET, LOW);
	

	_SPIManager->transfer(command);
}

#endif
