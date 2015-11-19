#pragma once

#include "Point.h"
#include "LineDetector.h"
#include "Anchor.h"

#define C_MIN_ANGLE 80.0
#define C_MAX_ANGLE 100.0

/**
* \class	AnchorDetector
*
* \brief	Looks for anchors by finding multiple lines and looking for there relation
*/
class AnchorDetector
{
public:
	AnchorDetector(volatile Error *e);
	bool newPoint(Point p);
	Anchor getLast();
private:
	LineDetector _lineDetector;
	Line _last;
	Anchor _lastAnchor;
	int _count;
};

