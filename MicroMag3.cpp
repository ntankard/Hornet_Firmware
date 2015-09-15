#include "MicroMag3.h"

#ifdef USE_MICROMAG3

// register map
#define X_ADDR 0b01100001
#define Y_ADDR 0b01100010
#define Z_ADDR 0b01100011
const uint8_t ADD[] = { X_ADDR, Y_ADDR, Z_ADDR };

//-----------------------------------------------------------------------------------------------------------------------------

MicroMag3::MicroMag3(volatile Error *e) :_SPIManager(e)
{
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

	TP("1");

	// atempt to read
	sendCommand(ADD[_sensor]);
	TP("2");
	// wait for the message
	setupTime.start(10000);
	while (digitalRead(C_MAG_DRDY) == LOW)
	{
		if (setupTime.hasTimeOut())
		{
			TP("TIMEOUT");
			return false;
		}
	}
	TP("3");
	// check the validity of the data
	uint8_t byte_H, byte_L;
	byte_H = _SPIManager.transfer(0);
	byte_L = _SPIManager.transfer(0);
	if (byte_H == 0 && byte_L == 0)
	{
		return false;
	}
	TP("4");
	// start the next read
	sendCommand(ADD[_sensor]);
	_lastRead.start(C_MAG_MAX_READ_TIME);
	TP("5");
	
	// check for varying data (can be static non0 if not conected
	/*int16_t last[3];
	setupTime.start(1000);
	while (!update())
	{
		if (setupTime.hasTimeOut())
		{
			return false;
		}
	}
	getData(last);
	for (int i = 0; i < 10; i++)
	{
		setupTime.start(1000);
		while (!update())
		{
			if (setupTime.hasTimeOut())
			{
				return false;
			}
		}
		if (_lastValid[0] != last[0] || _lastValid[1] != last[1] || _lastValid[2] != last[2] )
		{
			return true;
		}
		getData(last);
	}
	return false;*/
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool MicroMag3::update()
{
	//uint8_t data[2];
	if (digitalRead(C_MAG_DRDY) == HIGH)
	{
		uint8_t byte_H, byte_L;
		byte_H = _SPIManager.transfer(0);
		byte_L = _SPIManager.transfer(0);

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
			_e->add(E_HARDWARE_FAILURE,__LINE__);
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
	delay(1);
	digitalWrite(C_MAG_RESET, LOW);
	
	_SPIManager.transfer(command);
}

#endif
//byte response = SPI.transfer(4, 0xFF);