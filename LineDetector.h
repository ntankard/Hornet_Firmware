#pragma once

#include "RollingWindow.h"

class LineDetector
{
public:
	LineDetector();
	~LineDetector();
private:
	//RollingWindow<Point, C_MIN_LINE_POINTS> _lead;

	// line caculations
	float _sumX;
	float _sumY;
	float _sumXY;
	float _sumXX;

	// total corelation
	float _TXMean;
	float _TYMean;
	float _TA;
	float _TB;
	float _TAB;
	float _TAA;
	float _TBB;

	// lead corelation
};

