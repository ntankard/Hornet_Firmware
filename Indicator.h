#pragma once

#include "arduino.h"

#if ENABLE_INDICATOR == ENABLED

class Indicator {

public:

	Indicator();

	void on();
	void off();

	void setDisplay(int setting, int blinks, int rate);

	void run();

protected:

	virtual void lightOn(int setting) = 0;
	virtual void lightOff() = 0;

	bool _isOn;
	int _blinks;
	unsigned long _rate;
	int _setting;
	unsigned long _pastTime;
	int _pinState;
	bool _isBreak;
	int _doneBlinks;

	const int ON = LOW;
	const int OFF = HIGH;
};

#else

class Indicator {
public:
	Indicator(){}
	void run(){}
	void on(){}
	void off(){}
	void setDisplay(int setting, int blinks, int rate);
};

#endif


