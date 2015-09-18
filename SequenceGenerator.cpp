#include "SequenceGenerator.h"
#include "Arduino.h"

SequenceGenerator::SequenceGenerator()
{
	_rate = 1000;
	_blinks = 0;
	_gapMultiplyer = 0;
	reset();
}

//-----------------------------------------------------------------------------------------------------------------------------

void SequenceGenerator::set(unsigned long rate, unsigned blinks, unsigned gapMultiplyer)
{
	
	_rate = rate;
	_blinks = blinks;
	_gapMultiplyer = gapMultiplyer;
	reset();
}

//-----------------------------------------------------------------------------------------------------------------------------

bool SequenceGenerator::isHigh()
{
	return _isHigh;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool SequenceGenerator::run()
{
	if (_blinks == 0)
	{
		return false;
	}
	else if (_blinks == 1)
	{
		return runBlink();
	}
	else
	{
		return runSequence();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

bool SequenceGenerator::runBlink()
{
	unsigned long currentMillis = millis();

	if (currentMillis > (_pastTime + _rate))
	{
		_pastTime += _rate;
		_isHigh = !_isHigh;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool SequenceGenerator::runSequence()
{
	unsigned long currentMillis = millis();
	bool pastIsHigh = _isHigh;

	if (_isBreak)
	{
		if (currentMillis >= (_pastTime + _rate))
		{
			_doneBlinks++;
			if (_doneBlinks >= _gapMultiplyer * 2){
				// end of a break
				_isHigh = false;
				_pastTime += (_rate * _gapMultiplyer);
				_isBreak = false;
				_doneBlinks = 0;
			}
		}
	}
	else
	{
		if (currentMillis >= (_pastTime + _rate))
		{
			if (_isHigh == false)
			{
				// end of a regular gap
				_isHigh = true;
				_pastTime += _rate;
			}
			else
			{
				// end of a on period
				_isHigh = false;
				_pastTime += _rate;
				if (_blinks != 1)
				{
					// pattern
					_doneBlinks++;
					if (_doneBlinks >= _blinks)
					{
						// time for a long break
						_isBreak = true;
						_doneBlinks = 0;
					}
				}
			}
		}
	}
	
	return (_isHigh != pastIsHigh);
}

//-----------------------------------------------------------------------------------------------------------------------------

void SequenceGenerator::reset()
{
	_pastTime = millis();
	_isHigh = false;
	_isBreak = false;
	_doneBlinks = 0;

	if (_blinks == 0)
	{
		_isHigh = true;
	}
}
