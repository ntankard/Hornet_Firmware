#pragma once 
#include "Arduino.h"
#include "math.h"

class Feature
{
public:
	Feature(Pattern* startPattern, Pattern* endPattern)
	{
		_startPattern = startPattern;
		_endPattern = endPattern;
	}
private:
	Pattern* _startPattern;
	Pattern* _endPattern;

	//@TODO Add in feature code from laptop****
};
