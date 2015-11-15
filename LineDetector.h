#pragma once

#include "RollingCorrelation.h"
#include "Line.h"

#define C_CORRELATION_SIZE 10
#define C_THRESHOLD 0.95
#define C_MIN_SIZE 10

class LineDetector
{
public:
	LineDetector(volatile Error *e);
	bool newPoint(Point p);
	Line getLast();
private:
	bool _isLine;
	bool _isPos;
	RollingCorrelation<C_CORRELATION_SIZE> _detector;
	Point _start;
	Point _end;
	Line _lastLine;
	int _num;
};

