#pragma once
#include "CONFIG.h"

#ifdef USE_APM_INDICATOR

#include "Indicator.h"
#include "arduino.h"

class APM_Indicator :public Indicator
{
public:
	enum Color{ BLUE =0, YELLOW=1, RED=2, PURPLE=3, ORANGE=4, MAGENTA=5};
	APM_Indicator();
protected:
	void lightOn(int setting);
	void lightOff();

	const int ON = LOW;
	const int OFF = HIGH;
	const int onOffState[6][3] = { { ON, OFF, OFF }, { OFF, OFF, ON }, { ON, OFF, ON }, { ON, OFF, ON }, { OFF, ON, ON }, { ON, ON, OFF } };
};

#endif