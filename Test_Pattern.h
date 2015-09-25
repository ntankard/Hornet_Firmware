#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Pattern.h"

test(Pattern_Setup)
{
	Pattern pattern;
	assertEqual(pattern.getStartCoordX(), 0);
	assertEqual(pattern.getStartCoordY(), 0);
	assertEqual(pattern.getEndCoordX(), 0);
	assertEqual(pattern.getEndCoordY(), 0);
	assertEqual(pattern.getAngle(), 0);
	assertEqual(pattern.getState(), NOT_SET);
}

test(Pattern_Set)
{
	Pattern pattern;
	Point startPoint;
	Point endPoint;
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	pattern.setPattern(&startPoint, &endPoint);
	assertEqual(pattern.getStartCoordX(), 0);
	assertEqual(pattern.getStartCoordY(), 0);
	assertEqual(pattern.getEndCoordX(), 5);
	assertEqual(pattern.getEndCoordY(), 5);
	assertEqual(pattern.getAngle(), 45);
	assertEqual(pattern.getState(), SET);
}

#endif