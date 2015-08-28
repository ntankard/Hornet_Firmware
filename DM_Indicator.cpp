#include "DM_Indicator.h"

// rows on = HIGH
//comul on = LOW

#ifdef USE_DM_INDICATOR
#include "arduino.h"

const int ROWS[] = { CANODE_6, CANODE_10, CANODE_11, CANODE_3, CANODE_13 };
const int COLUMNS[] = { CANODE_9, CANODE_14, CANODE_8, CANODE_5, CANODE_1, CANODE_7, CANODE_2 };


const int SETTING_MAP[][4] = {	{ 0, 0, 1, 1 },
								{ 0, 0, 2, 2 } ,
								{ 0, 0, 3, 3 } ,
								{ 0, 0, 4, 4 } };

#define NUM_ROWS 5
#define NUM_COLLUNS 7

#define ROW_ON HIGH
#define ROW_OFF LOW
#define COLUMNS_ON LOW
#define COLUMNS_OFF HIGH

DM_Indicator::DM_Indicator()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		pinMode(ROWS[i], OUTPUT);
		digitalWrite(ROWS[i], ROW_OFF);
	}

	for (int i = 0; i < NUM_COLLUNS; i++)
	{
		pinMode(COLUMNS[i], OUTPUT);
		digitalWrite(COLUMNS[i], COLUMNS_OFF);
	}

	_lastSetting = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void DM_Indicator::lightOn(int setting)
{
	//@TODO add setting check

	if (setting >= 4)
	{
		return;
	}

	if (_lastSetting != setting)
	{
		lightOff();
	}

	_lastSetting = setting;

	digitalWrite(ROWS[SETTING_MAP[_lastSetting][0]], ROW_ON);
	digitalWrite(COLUMNS[SETTING_MAP[_lastSetting][1]], COLUMNS_ON);
	digitalWrite(ROWS[SETTING_MAP[_lastSetting][2]], ROW_ON);
	digitalWrite(COLUMNS[SETTING_MAP[_lastSetting][3]], COLUMNS_ON);
}

//-----------------------------------------------------------------------------------------------------------------------------

void DM_Indicator::lightOff()
{
	digitalWrite(ROWS[SETTING_MAP[_lastSetting][0]], ROW_OFF);
	digitalWrite(COLUMNS[SETTING_MAP[_lastSetting][1]], COLUMNS_OFF);
	digitalWrite(ROWS[SETTING_MAP[_lastSetting][2]], ROW_OFF);
	digitalWrite(COLUMNS[SETTING_MAP[_lastSetting][3]], COLUMNS_OFF);
}

#endif
