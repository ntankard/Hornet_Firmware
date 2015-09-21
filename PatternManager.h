#pragma once

#include "Pattern.h"

class PatternManager
{
public:
	PatternManager();
	void addPattern(Point* startPoint, Point* endPoint);
	void setupPattern(Point* startPoint, Point* endPoint);
	bool isSetup();
private:
	bool _setup;
	Pattern* _startPattern;
	Pattern* _endPattern;
};