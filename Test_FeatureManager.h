#pragma once

#if BUILD_TYPE == FOR_TEST

#include "FeatureManager.h"
#include "PatternManager.h"

test(FeatureManager_setup)
{
	FeatureManager* _featureManager = new FeatureManager();
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureManager->getFeatureList());
	assertEqual(iter.getNode()->getValue().getState(), FEATURE_HEAD);
	iter = iter.last();
	assertEqual(iter.getNode()->getValue().getState(), FEATURE_TAIL);
}

test(FeatureManager_AddFeature)
{
	FeatureManager* _featureManager = new FeatureManager();
	PatternManager* _patternManager = new PatternManager();
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager->addPattern(startPoint, endPoint);
	startPoint->setXY(5, 5);
	endPoint->setXY(10, 0);
	_patternManager->addPattern(startPoint, endPoint);
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureManager->getFeatureList());
	iter++;
	assertEqual(iter.getNode()->getValue().getState(), FEATURE_DATA);
	assertEqual(iter.getNode()->getValue().getEnterStartX(), 0);
	assertEqual(iter.getNode()->getValue().getEnterStartY(), 0);
	assertEqual(iter.getNode()->getValue().getEnterEndX(), 5);
	assertEqual(iter.getNode()->getValue().getEnterEndY(), 5);
	assertEqual(iter.getNode()->getValue().getExitStartX(), 5);
	assertEqual(iter.getNode()->getValue().getExitStartY(), 5);
	assertEqual(iter.getNode()->getValue().getExitEndX(), 10);
	assertEqual(iter.getNode()->getValue().getExitEndY(), 0);
}

test(FeatureManager_FeatureListSize)
{
	FeatureManager* _featureManager = new FeatureManager();
	PatternManager* _patternManager = new PatternManager();
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager->addPattern(startPoint, endPoint);
	startPoint->setXY(5, 5);
	endPoint->setXY(10, 0);
	_patternManager->addPattern(startPoint, endPoint);
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	assertEqual(_featureManager->featureListSize(), 3);
}

test(FeatureManager_ManageFeatures)
{
	FeatureManager* _featureManager = new FeatureManager();
	PatternManager* _patternManager = new PatternManager();
	Point* startPoint = new Point(DATA);
	startPoint->setXY(0, 0);
	Point* endPoint = new Point(DATA);
	endPoint->setXY(5, 5);
	_patternManager->addPattern(startPoint, endPoint);
	startPoint->setXY(5, 5);
	endPoint->setXY(10, 0);
	_patternManager->addPattern(startPoint, endPoint);
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureManager->getFeatureList());
	int size = _featureManager->featureListSize();
	iter++;
	iter.getNode()->getValue().setLife(0);
	iter++;
	iter.getNode()->getValue().setLife(0);
	iter++;
	iter.getNode()->getValue().setLife(0);
	_featureManager->manageFeatureList();
	assertEqual(_featureManager->featureListSize(), 3);
}

#endif