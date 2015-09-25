#pragma once

#if BUILD_TYPE == FOR_TEST

#include "FeatureManager.h"
#include "PatternManager.h"

test(FeatureManager_setup)
{
	FeatureManager* _featureManager = new FeatureManager();
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureManager->getFeatureList());
	assertEqual(iter.getNode()->getValue().getState(), FEATURE_HEAD);
	iter++;
	for (int i = 0; i < L_FEATURES_STORED; i++)
	{
		assertEqual(iter.getNode()->getValue().getState(), FEATURE_NULL); 
		iter++;
	}
	assertEqual(iter.getNode()->getValue().getState(), FEATURE_TAIL);
}

test(FeatureManager_AddFeature)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint(DATA);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureManager.getFeatureList());
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

test(FeatureManager_AddFeatureMultiple)
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
	for (int i = 0; i < L_FEATURES_STORED; i++)
	{
		_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
	}
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureManager->getFeatureList());
	iter++;
	for (int i = 0; i < L_FEATURES_STORED; i++)
	{
		assertEqual(iter.getNode()->getValue().getState(), FEATURE_DATA);
		assertEqual(iter.getNode()->getValue().getEnterStartX(), 0);
		assertEqual(iter.getNode()->getValue().getEnterStartY(), 0);
		assertEqual(iter.getNode()->getValue().getEnterEndX(), 5);
		assertEqual(iter.getNode()->getValue().getEnterEndY(), 5);
		assertEqual(iter.getNode()->getValue().getExitStartX(), 5);
		assertEqual(iter.getNode()->getValue().getExitStartY(), 5);
		assertEqual(iter.getNode()->getValue().getExitEndX(), 10);
		assertEqual(iter.getNode()->getValue().getExitEndY(), 0);
		iter++;
	}
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
	DoublyLinkedNodeIterator<Feature> iter = DoublyLinkedNodeIterator<Feature>(*_featureManager->getFeatureList());
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
	iter = DoublyLinkedNodeIterator<Feature>(*_featureManager->getFeatureList());
	iter++;
	assertEqual(iter.getNode()->getValue().getState(), FEATURE_DATA);
	iter++;
	assertEqual(iter.getNode()->getValue().getState(), FEATURE_DATA);
	iter++;
	assertEqual(iter.getNode()->getValue().getState(), FEATURE_DATA);
}

test(FeatureManager_featureExists_perfectMatch)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint(DATA);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	assertTrue(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

#endif