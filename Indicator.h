#pragma once

#include "arduino.h"

class Indicator {

public:

	enum Color{BLUE,YELLOW,RED};

	Indicator();
  
    void run();

	void setOn(Color c, bool isOn);

	void setBlinks(Color c,int b);

	void setBlinkRate(Color c,int r);


    
private:

	//const int BLUE = 0;
	//const int YELLOW = 1;
	//const int RED = 2;

	unsigned long _interval[3];
	bool _isOn[3];
	int _blinks[3];
	int _pin[3];
	int _pinState[3];

	bool _isBreak[3];
	int _doneBlinks[3];
	unsigned long _pastTime[3];

	int ON = LOW;
	int OFF = HIGH;
};


