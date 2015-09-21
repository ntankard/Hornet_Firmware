#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Pattern.h"

test(Pattern_setup)
{
	Pattern* pattern = new Pattern(SET);
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	pattern->setPattern(startPoint, endPoint);
	assertEqual(pattern->getStartCoordX(), 0);
	assertEqual(pattern->getStartCoordY(), 0);
	assertEqual(pattern->getEndCoordX(), 5);
	assertEqual(pattern->getEndCoordY(), 5);
	assertEqual(pattern->getAngle(), 45);
}

#endif