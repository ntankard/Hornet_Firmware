#include "Indicator.h"
#include "Arduino.h"
#include "APM_2_5_PINS.h"
#include "CONFIG.h"

#if ENABLE_INDICATOR == ENABLED

Indicator::Indicator()
{
	_isOn = false;

	_blinks = 1;
	_rate = 1000;
	_setting = 0;

	_isBreak = false;
	_pinIsOn = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::on()
{
	_isOn = true;

	if (_isOn)
	{
		// reset
		_isBreak = false;
		_doneBlinks = 0;
		_pinIsOn = false;
		_pastTime = millis();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::off()
{
	lightOff();
	_isOn = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::setDisplay(int setting, int blinks, int rate)
{
	_setting = setting;
	_blinks = blinks;
	_rate = rate;
}

//-----------------------------------------------------------------------------------------------------------------------------

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
				_pinIsOn = true;
				lightOn(_setting);
				_pastTime = currentMillis;
				_isBreak = false;
				_doneBlinks = 0;
			}
		}
		else
		{
			if (currentMillis >= (_pastTime + _rate))
			{
				if (_pinIsOn == false)
				{
					// end of a regular gap
					_pinIsOn = true;
					lightOn(_setting);
					_pastTime = currentMillis;
				}
				else
				{
					// end of a on period
					_pinIsOn = false;
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

#endif
