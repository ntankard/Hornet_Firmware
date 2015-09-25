#pragma once

#if BUILD_TYPE == FOR_TEST

#include "PatternManager.h"

test(PatternManager_Setup)
{
	PatternManager _patternManager;
	assertEqual(_patternManager.getEntryPattern()->getState(), NOT_SET);
	assertEqual(_patternManager.getExitPattern()->getState(), NOT_SET);
}

test(PatternManager_Setup_Patterns)
{
	PatternManager _patternManager;
	Point point;
	point.setXY(0, 0);
	_patternManager.addPattern(&point, &point);
	point.setXY(2, 2);
	_patternManager.addPattern(&point, &point);
	assertTrue(_patternManager.isSetup());
	assertEqual(_patternManager.getEntryPattern()->getStartCoordX(), 0);
	assertEqual(_patternManager.getExitPattern()->getStartCoordX(), 2);
}

test(PatternManager_isFeature_RightAngleCorner)
{
	PatternManager _patternManager;
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager.addPattern(startPoint, endPoint);
	startPoint->setXY(5, 5);
	endPoint->setXY(10, 0);
	_patternManager.addPattern(startPoint, endPoint);
	assertTrue(_patternManager.isFeature());
}

test(PatternManager_isFeature_OnYBoundRange)
{
	PatternManager* _patternManager = new PatternManager();
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager->addPattern(startPoint, endPoint);
	startPoint->setXY(5, 5 + L_PATTERN_RANGE_IN_FEATURE);
	endPoint->setXY(10, 0 + L_PATTERN_RANGE_IN_FEATURE);
	_patternManager->addPattern(startPoint, endPoint);
	assertTrue(_patternManager->isFeature());
}

test(PatternManager_isFeature_OnXBoundRange)
{
	PatternManager* _patternManager = new PatternManager();
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager->addPattern(startPoint, endPoint);
	startPoint->setXY(5 + L_PATTERN_RANGE_IN_FEATURE, 5);
	endPoint->setXY(10 + L_PATTERN_RANGE_IN_FEATURE, 0);
	_patternManager->addPattern(startPoint, endPoint);
	assertTrue(_patternManager->isFeature());
}

test(PatternManager_isFeature_OnXYBoundRange)
{
	PatternManager* _patternManager = new PatternManager();
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager->addPattern(startPoint, endPoint);
	startPoint->setXY(5 + L_PATTERN_RANGE_IN_FEATURE, 5 + L_PATTERN_RANGE_IN_FEATURE);
	endPoint->setXY(10 + L_PATTERN_RANGE_IN_FEATURE, 0 + L_PATTERN_RANGE_IN_FEATURE);
	_patternManager->addPattern(startPoint, endPoint);
	assertTrue(_patternManager->isFeature());
}

test(PatternManager_isFeature_OutsideYBoundRange)
{
	PatternManager* _patternManager = new PatternManager();
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager->addPattern(startPoint, endPoint);
	startPoint->setXY(5, 5 + L_PATTERN_RANGE_IN_FEATURE + 1);
	endPoint->setXY(10, 0 + L_PATTERN_RANGE_IN_FEATURE + 1);
	_patternManager->addPattern(startPoint, endPoint);
	assertFalse(_patternManager->isFeature());
}

test(PatternManager_isFeature_OutsideXBoundRange)
{
	PatternManager* _patternManager = new PatternManager();
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager->addPattern(startPoint, endPoint);
	startPoint->setXY(5 + L_PATTERN_RANGE_IN_FEATURE + 1, 5);
	endPoint->setXY(10 + L_PATTERN_RANGE_IN_FEATURE + 1, 0);
	_patternManager->addPattern(startPoint, endPoint);
	assertFalse(_patternManager->isFeature());
}

test(PatternManager_isFeature_OutsideXYBoundRange)
{
	PatternManager* _patternManager = new PatternManager();
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager->addPattern(startPoint, endPoint);
	startPoint->setXY(5 + L_PATTERN_RANGE_IN_FEATURE + 1, 5 + L_PATTERN_RANGE_IN_FEATURE + 1);
	endPoint->setXY(10 + L_PATTERN_RANGE_IN_FEATURE + 1, 0 + L_PATTERN_RANGE_IN_FEATURE + 1);
	_patternManager->addPattern(startPoint, endPoint);
	assertFalse(_patternManager->isFeature());
}

//TODO ADD MORE TESTS (IMPERFECT CORNERS ETC ETC)

#endif