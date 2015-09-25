#include "EngineDriver.h"
#include "Arduino.h"

#define MIN 60
#define MAX 130
#define DIF (MAX-MIN)

EngineDriver::EngineDriver()
{
	_isOn = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void EngineDriver::attach(int PWMPin)
{
	_engine.attach(PWMPin);
	_engine.write(0);
}

//-----------------------------------------------------------------------------------------------------------------------------

void EngineDriver::on()
{
	if (!_isOn && _engine.attached())
	{
		_engine.write(MIN);
	}
	_isOn = true;
	
}

//-----------------------------------------------------------------------------------------------------------------------------

void EngineDriver::off()
{
	if (_isOn)
	{
		_engine.write(MIN);
		delay(500);				// prevents a hard stop of the motors
		_engine.write(0);
	}
	_isOn = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool EngineDriver::isOn()
{
	return _isOn;
}

//-----------------------------------------------------------------------------------------------------------------------------

void EngineDriver::setPower(double p)
{
	if (p < 0 || p>100)
	{
		return;
	}
	if (_isOn)
	{
		_engine.write(MIN + ((double)DIF*(p / 100.0)));
	}
}
