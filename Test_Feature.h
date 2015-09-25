#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Feature.h"

test(Feature_Setup)
{
	Feature f1;
	assertEqual(f1.getState(), FEATURE_NULL);
	assertEqual(f1.getEnterStartX(), 0);
	assertEqual(f1.getEnterStartY(), 0);
	assertEqual(f1.getEnterEndX(), 0);
	assertEqual(f1.getEnterEndY(), 0);
	assertEqual(f1.getExitStartX(), 0);
	assertEqual(f1.getExitStartY(), 0);
	assertEqual(f1.getExitEndX(), 0);
	assertEqual(f1.getExitEndY(), 0);
	assertEqual(f1.getLife(), 0);
	assertEqual(f1.getOccurances(), 0);
}

test(Feature_Set)
{
	Point p1;
	p1.setXY(2, 2);
}
#endif