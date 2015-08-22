#pragma once

#include "arduino.h"

#if ENABLE_INDICATOR == ENABLED

class Indicator {

public:

	enum Color{BLUE,YELLOW,RED,PURPLE,ORANGE,MAGENTA};

	//blue red yellow
	const int onOffState[6][3] = { { ON, OFF, OFF }, { OFF, OFF, ON }, { ON, OFF, ON }, { ON, OFF, ON }, { OFF, ON, ON }, {ON,ON,OFF} };

	Indicator();
  
    void run();

	void on();

	void off();

	void setDisplay(Color c, int blinks, unsigned long rate);


	void setOn(Color c, bool isOn);

	void setBlinks(Color c,int b);

	void setBlinkRate(Color c,int r);


    
private:


	void lightOn();

	void lightOff();


	bool _isOn;
	Color _c;
	int _blinks;
	unsigned long _rate;
	unsigned long _pastTime;
	int _pinState;
	bool _isBreak;
	int _doneBlinks;

	//unsigned long _interval;

	//const int BLUE = 0;
	//const int YELLOW = 1;
	//const int RED = 2;

	/*unsigned long _interval[3];
	bool _isOn[3];
	int _blinks[3];
	int _pin[3];
	int _pinState[3];

	bool _isBreak[3];
	int _doneBlinks[3];
	unsigned long _pastTime[3];*/

	const int ON = LOW;
	const int OFF = HIGH;
};

#else
class Indicator {

public:
	enum Color{ BLUE, YELLOW, RED, PURPLE, ORANGE, MAGENTA };
	Indicator(){}
	void run(){}
	void on(){}
	void off(){}
	void setDisplay(Color c, int blinks, unsigned long rate){}
	void setOn(Color c, bool isOn){}
	void setBlinks(Color c, int b){}
	void setBlinkRate(Color c, int r){}
};
#endif


