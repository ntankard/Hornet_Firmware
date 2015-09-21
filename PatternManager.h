#pragma once

#include "CONFIG.h"
#include "Pattern.h"

class PatternManager
{
public:
	PatternManager();
	void addPattern(Point* startPoint, Point* endPoint);
	void setupPattern(Point* startPoint, Point* endPoint);
	bool isFeature();
	Pattern* getEnterPattern();
	Pattern* getExitPattern();
	bool isSetup();
private:
	bool _setup;
	Pattern* _enterPattern;
	Pattern* _exitPattern;
};