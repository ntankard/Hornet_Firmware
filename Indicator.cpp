#include "Indicator.h"
#include "Arduino.h"
#include "APM_2_5_PINS.h"

Indicator::Indicator()
{
	_isOn = false;
	_c = BLUE;
	_blinks = 1;
	_rate = 1000;
	_isBreak = false;

	pinMode(BLUE_LED, OUTPUT);
	digitalWrite(BLUE_LED, OFF);
	pinMode(RED_LED, OUTPUT);
	digitalWrite(RED_LED, OFF);
	pinMode(YELLOY_LED, OUTPUT);
	digitalWrite(YELLOY_LED, OFF);

	/*_pin[0] = BLUE_LED;
	_pin[1] = YELLOY_LED;
	_pin[2] = RED_LED;

	for (int i = 0; i < 3; i++)
	{
		_interval[i]=500;
		_isOn[i] = false;
		_blinks[i] = 3;
		_pinState[i] = OFF;
		pinMode(_pin[i], OUTPUT);
		digitalWrite(_pin[i], _pinState[i]);
	}*/
}

void Indicator::run()
{
	unsigned long currentMillis = millis();

		if (_isOn)
		{
			if (_isBreak)
			{
				if (currentMillis >= (_pastTime + (_rate * 3)))
				{
					// end of a break
					_pinState = ON;
					lightOn();
					_pastTime = currentMillis;
					_isBreak = false;
					_doneBlinks = 0;
				}
			}
			else
			{
				if (currentMillis >= (_pastTime + _rate))
				{
					if (_pinState == OFF)
					{
						// end of a regular gap
						_pinState = ON;
						lightOn();
						_pastTime = currentMillis;
					}
					else
					{
						// end of a on period
						_pinState = OFF;
						lightOff();
						_pastTime = currentMillis;
						if (_blinks != 1)
						{
							// pattern
							_doneBlinks ++;
							if (_doneBlinks >= _blinks)
							{
								// time for a long break
								_isBreak = true;
							}
						}
					}
				}
			}
		}
}




void Indicator::on()
{
	_isOn = true;

	if (_isOn)
	{
			// reset
		_isBreak = false;
		_doneBlinks = 0;
		_pastTime = millis();
	}
}

void Indicator::off()
{
	lightOff();
	_isOn = false;
}

void Indicator::setDisplay(Color c, int blinks, unsigned long rate)
{
	_c = c;
	_blinks = blinks;
	_rate = rate;
}

void Indicator::lightOn()
{
	digitalWrite(BLUE_LED, onOffState[_c][0]);
	digitalWrite(RED_LED, onOffState[_c][1]);
	digitalWrite(YELLOY_LED, onOffState[_c][2]);
}

void Indicator::lightOff()
{
	digitalWrite(BLUE_LED, OFF);
	digitalWrite(RED_LED, OFF);
	digitalWrite(YELLOY_LED, OFF);
}

/*
void Indicator::setOn(Color c, bool isOn)
{

	if (_isOn[c] != isOn)
	{
		if (isOn)
		{
			// reset
			_isBreak[c] = false;
			_doneBlinks[c] = 0;
			_pastTime[c] = millis();
		}
		_isOn[c] = isOn;
		_pinState[c] = OFF;
		digitalWrite(_pin[c], _pinState[c]);
	}
}

void Indicator::setBlinks(Color c, int b)
{
	_blinks[c] = b;
}

void Indicator::setBlinkRate(Color c, int r)
{
	_interval[c] = r;
}*/

