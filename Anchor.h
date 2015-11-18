#pragma once

#include "Line.h"
#include "math.h"
class Anchor
{
public:
	Anchor();
	void setLines(Line start, Line end);
	Point getAnchorPoint();

	Line getStart(){ return _start; };
	Line getEnd(){ return _end; }
private:
	Line _start;
	Line _end;

	bool _isInvert;
};

