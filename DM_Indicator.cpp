#include "DM_Indicator.h"

// rows on = HIGH
//comul on = LOW

#ifdef USE_DM_INDICATOR
#include "arduino.h"

const int ROWS[] = { CANODE_6, CANODE_10, CANODE_11, CANODE_3, CANODE_13 };
const int COLUMNS[] = { CANODE_9, CANODE_14, CANODE_8, CANODE_12, CANODE_1, CANODE_7, CANODE_2 };

#define NUM_ROWS 5
#define NUM_COLLUNS 7

const int MATRIX_SIZE = ((NUM_ROWS - 1) * (NUM_COLLUNS -1));

#define ROW_ON HIGH
#define ROW_OFF LOW
#define COLUMNS_ON LOW
#define COLUMNS_OFF HIGH

Indicator::Indicator(Error *e)
{
	_e = e;

	for (int i = 0; i < (NUM_ROWS); i++)
	{
		pinMode(ROWS[i], OUTPUT);
	}

	for (int i = 0; i < (NUM_COLLUNS); i++)
	{
		pinMode(COLUMNS[i], OUTPUT);
	}

	safeOff();
	reset();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::reset()
{
	for (int i = 0; i < (NUM_ROWS-1); i++)
	{
		digitalWrite(ROWS[i], ROW_OFF);
	}

	for (int i = 0; i < (NUM_COLLUNS - 1); i++)
	{
		digitalWrite(COLUMNS[i], COLUMNS_OFF);
	}

	_isOn = false;

	_blinks = 1;
	_rate = 1000;
	_setting_1 = 0;
	_setting_2 = 0;

	_isBreak = false;
	_pinIsOn = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::on()
{
	reset();
	_isOn = true;
	lightOn(_setting_1,_setting_2);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::off()
{
	lightOff();
	_isOn = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::setDisplay(int setting_1, int setting_2, int blinks, int rate)
{
	if (setting_1 < 0 || setting_1 >= MATRIX_SIZE || setting_2 < 0 || setting_2 >= MATRIX_SIZE)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
		return;
	}



	reset();
	_setting_1 = setting_1;
	_setting_2 = setting_2;
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
				lightOn(_setting_1,_setting_2);
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
					lightOn(_setting_1, _setting_2);
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
						_doneBlinks++;
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

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::safeOn()
{
	digitalWrite(ROWS[4], ROW_ON);
	digitalWrite(COLUMNS[6], COLUMNS_ON);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::safeOff()
{
	digitalWrite(ROWS[4], ROW_OFF);
	digitalWrite(COLUMNS[6], COLUMNS_OFF);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::lightOn(int setting_1, int setting_2)
{
	// asume that settings are valid as they are gate checked by setParam

	digitalWrite(setting_1%NUM_ROWS, ROW_ON);
	digitalWrite(setting_1/NUM_ROWS, COLUMNS_ON);
	digitalWrite(setting_2%NUM_ROWS, ROW_ON);
	digitalWrite(setting_2 / NUM_ROWS, COLUMNS_ON);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Indicator::lightOff()
{
	digitalWrite(_setting_1%NUM_ROWS, ROW_OFF);
	digitalWrite(_setting_1 / NUM_ROWS, COLUMNS_OFF);
	digitalWrite(_setting_2%NUM_ROWS, ROW_OFF);
	digitalWrite(_setting_2 / NUM_ROWS, COLUMNS_OFF);
}

#endif


// row col
/*
const int SETTING_MAP[][4] = {
{ 0, 0, 0, 0 },
{ 1, 0, 1, 0 },
{ 2, 0, 2, 0 },
{ 3, 0, 3, 0 },
{ 0, 1, 0, 1 },
{ 1, 1, 1, 1 },
{ 2, 1, 2, 1 },
{ 3, 1, 3, 1 },
{ 0, 2, 0, 2 },
{ 1, 2, 1, 2 },
{ 2, 2, 2, 2 },
{ 3, 2, 3, 2 },
{ 0, 3, 0, 3 },
{ 1, 3, 1, 3 },
{ 2, 3, 2, 3 },
{ 3, 3, 3, 3 },
{ 0, 4, 0, 4 },
{ 1, 4, 1, 4 },
{ 2, 4, 2, 4 },
{ 3, 4, 3, 4 },
{ 0, 0, 0, 0 },
{ 1, 0, 1, 0 },
{ 2, 0, 2, 0 },
{ 3, 0, 3, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 1, 1 } ,
{ 0, 0, 2, 2 } ,
{ 0, 0, 3, 3 } };*/