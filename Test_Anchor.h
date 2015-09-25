#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Anchor.h"

test(Anchor_Setup)
{
	Anchor a1;
	assertEqual(a1.getState(), ANCHOR_NULL);
	assertEqual(a1.getEnterStartX(), 0);
	assertEqual(a1.getEnterStartY(), 0);
	assertEqual(a1.getEnterEndX(), 0);
	assertEqual(a1.getEnterEndY(), 0);
	assertEqual(a1.getExitStartX(), 0);
	assertEqual(a1.getExitStartY(), 0);
	assertEqual(a1.getExitEndX(), 0);
	assertEqual(a1.getExitEndY(), 0);

}

test(Anchor_Set)
{
	Anchor a1;
	Feature feature;
	Pattern pattern;
	Pattern pattern2;
	Point point;
	Point point2;
	point.setXY(1, 2);
	point2.setXY(3, 4);
	pattern.setPattern(&point, &point2);
	point.setXY(5, 6);
	point2.setXY(7, 8);
	pattern2.setPattern(&point, &point2);
	feature.setFeature(&pattern, &pattern2);
	a1.setAnchor(&feature);
	assertEqual(a1.getState(), ANCHOR_DATA);
	assertEqual(a1.getEnterStartX(), 1);
	assertEqual(a1.getEnterStartY(), 2);
	assertEqual(a1.getEnterEndX(), 3);
	assertEqual(a1.getEnterEndY(), 4);
	assertEqual(a1.getExitStartX(), 5);
	assertEqual(a1.getExitStartY(), 6);
	assertEqual(a1.getExitEndX(), 7);
	assertEqual(a1.getExitEndY(), 8);
}

#endif