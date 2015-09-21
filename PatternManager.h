#pragma once

#include "Pattern.h"

class PatternManager
{
public:
	PatternManager();
	void addPattern(Point* startPoint, Point* endPoint);
private:
	bool _setup;
	Pattern* _startPattern;
	Pattern* _endPattern;
};