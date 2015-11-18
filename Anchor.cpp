#include "Anchor.h"
#include "math.h"
#include "Arduino.h"

Anchor::Anchor()
{
	_isInvert = false;
}

void Anchor::setLines(Line start, Line end)
{
	_start = start;
	_end = end;

	if (abs(_start.getEnd().getAngle() - _end.getStart().getAngle()) < abs(_end.getEnd().getAngle() - _start.getStart().getAngle()))
	{
		_isInvert = false;
	}
	else
	{
		_isInvert = true;
	}
}

Point Anchor::getAnchorPoint()
{
	if (!_isInvert)
	{
		return _start.getStart();
	}
	return _end.getStart();
}

