#include "Indicator.h"
#include "Arduino.h"
#include "APM_2_5_PINS.h"

Indicator::Indicator()
{
	_pin[0] = BLUE_LED;
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
	}
}

void Indicator::run()
{
	unsigned long currentMillis = millis();

	for (int i = 0; i < 3; i++)
	{
		if (_isOn[i])
		{
			if (_isBreak[i])
			{
				if (currentMillis >= (_pastTime[i] + (_interval[i] * 3)))
				{
					// end of a break
					_pinState[i] = ON;
					_pastTime[i] = currentMillis;
					_isBreak[i] = false;
					_doneBlinks[i] = 0;
				}
			}
			else
			{
				if (currentMillis >= (_pastTime[i] + _interval[i]))
				{
					if (_pinState[i] == OFF)
					{
						// end of a regular gap
						_pinState[i] = ON;
						_pastTime[i] = currentMillis;
					}
					else
					{
						// end of a on period
						_pinState[i] = OFF;
						_pastTime[i] = currentMillis;
						if (_blinks[i] != 1)
						{
							// pattern
							_doneBlinks[i] ++;
							if (_doneBlinks[i] >= _blinks[i])
							{
								// time for a long break
								_isBreak[i] = true;
							}
						}
					}
				}
			}
		}

		digitalWrite(_pin[i], _pinState[i]);
	}


}

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
}

