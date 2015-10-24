#include "RBG_Indicator.h"

// rows on = HIGH
//comul on = LOW

#ifdef USE_RBG_INDICATOR
#include "arduino.h"

//-----------------------------------------------------------------------------------------------------------------------------

Indicator::Indicator(volatile Error *e)
{
	_e = e;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Indicator::start()
{
	for (int i = 0; i < (NUM_LIGHTS); i++)
	{
		pinMode(LIGHT_PINS[i], OUTPUT);
		digitalWrite(LIGHT_PINS[i], LOW);
	}

	_setting = 0;
	_blinks = 0;
	_rate = 500;

	safeOff();
	_sequenceGenerator.set(500, 0, 0);	//default is solid on

	on();

	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------




//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::on()
{
	_sequenceGenerator.set(_rate, _blinks, 3);	//reset
	_isOn = true;
	if (_sequenceGenerator.isHigh())
	{
		lightOn(_setting);
	}
	else
	{
		lightOff();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::off()
{
	_isOn = false;
	lightOff();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::setDisplay(int setting,  int blinks, int rate)
{
	if (_setting < 0 || _setting >= NUM_SETTINGS)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
		return;
	}

	// reset
	lightOff();
	_sequenceGenerator.set(rate, blinks, 3);

	_setting = setting;
	_blinks = blinks;
	_rate = rate;

	if (_isOn)
	{
		if (_sequenceGenerator.isHigh())
		{
			lightOn(_setting);
		}
		else
		{
			lightOff();
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Indicator::run()
{
	if (_isOn)
	{
		if (_sequenceGenerator.run())
		{
			if (_sequenceGenerator.isHigh())
			{
				lightOn(_setting);
			}
			else
			{
				lightOff();
			}
		}
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::safeOn()
{
	digitalWrite(LIGHT_PINS[SAFE_LIGHT], HIGH);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::safeOff()
{
	digitalWrite(LIGHT_PINS[SAFE_LIGHT], LOW);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::lightOn(int setting)
{
	// asume that settings are valid as they are gate checked by setParam
	digitalWrite(LIGHT_PINS[0], SETIINGS[setting][0]);
	digitalWrite(LIGHT_PINS[1], SETIINGS[setting][1]);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::lightOff()
{
	digitalWrite(LIGHT_PINS[0], LOW);
	digitalWrite(LIGHT_PINS[1], LOW);
}

#endif
