#include "APM_Indicator.h"
#include "CONFIG.h"

#ifdef USE_APM_INDICATOR

APM_Indicator::APM_Indicator() :Indicator()
{
	pinMode(BLUE_LED, OUTPUT);
	digitalWrite(BLUE_LED, OFF);
	pinMode(RED_LED, OUTPUT);
	digitalWrite(RED_LED, OFF);
	pinMode(YELLOY_LED, OUTPUT);
	digitalWrite(YELLOY_LED, OFF);
}

//-----------------------------------------------------------------------------------------------------------------------------

void APM_Indicator::lightOn(int setting)
{
	digitalWrite(BLUE_LED, onOffState[setting][0]);
	digitalWrite(RED_LED, onOffState[setting][1]);
	digitalWrite(YELLOY_LED, onOffState[setting][2]);
}

//-----------------------------------------------------------------------------------------------------------------------------

void APM_Indicator::lightOff()
{
	digitalWrite(BLUE_LED, OFF);
	digitalWrite(RED_LED, OFF);
	digitalWrite(YELLOY_LED, OFF);
}

#endif
