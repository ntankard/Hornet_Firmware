#pragma once

#if BUILD_TYPE == FOR_TEST

#include "FeatureManager.h"
#include "PatternManager.h"

test(FeatureManager_setup)
{
	FeatureManager _featureManager;
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
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
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
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
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint;
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	for (int i = 0; i < L_FEATURES_STORED; i++)
	{
		_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	}
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
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
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint;
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	assertEqual(_featureManager.featureListSize(), 3);
}

test(FeatureManager_ManageFeatures)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	startPoint.setXY(0, 0);
	Point endPoint;
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	int size = _featureManager.featureListSize();
	iter++;
	iter.getNode()->getValue().setLife(0);
	iter++;
	iter.getNode()->getValue().setLife(0);
	iter++;
	iter.getNode()->getValue().setLife(0);
	_featureManager.manageFeatureList();
	assertEqual(_featureManager.featureListSize(), 3);
	iter = DoublyLinkedNodeIterator<Feature>(*_featureManager.getFeatureList());
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

test(FeatureManager_featureExists_OccuranceUpdate)
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
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	assertEqual(iter.getNode()->getValue().getOccurances(), 1);
}

test(FeatureManager_isAnchor)
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
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	for (int i = L_FEATURE_OCCURANCES; i > 0; i--)
	{
		_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	}
	assertTrue(_featureManager.isAnchor());
}

test(FeatureManager_isAnchor_getRecurringFeature)
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
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	for (int i = L_FEATURE_OCCURANCES; i > 0; i--)
	{
		_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	}
	assertEqual(_featureManager.featureListSize(), 1)
	if (_featureManager.isAnchor())
	{
		Feature* anchor = _featureManager.getReccuringFeature();
	}
	assertEqual(_featureManager.featureListSize(), 0)
}

test(FeatureManager_featureExists_EntryOnXBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5 + L_FEATURE_RANGE_TOLERANCE, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertTrue(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_EntryOnYBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5 + L_FEATURE_RANGE_TOLERANCE);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertTrue(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_EntryOnXYBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5 + L_FEATURE_RANGE_TOLERANCE, 5 + L_FEATURE_RANGE_TOLERANCE);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertTrue(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_ExitOnXBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5 + L_FEATURE_RANGE_TOLERANCE, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertTrue(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_ExitOnYBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5, 5 + L_FEATURE_RANGE_TOLERANCE);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertTrue(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_ExitOnXYBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5 + L_FEATURE_RANGE_TOLERANCE, 5 + L_FEATURE_RANGE_TOLERANCE);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertTrue(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_EntryOutsideXBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5 + L_FEATURE_RANGE_TOLERANCE + 1, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertFalse(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_EntryOutsideYBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5 + L_FEATURE_RANGE_TOLERANCE + 1);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertFalse(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_EntryOutsideXYBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5 + L_FEATURE_RANGE_TOLERANCE + 1, 5 + L_FEATURE_RANGE_TOLERANCE + 1);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertFalse(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_ExitOutsideXBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5 + L_FEATURE_RANGE_TOLERANCE + 1, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertFalse(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_ExitOutsideYBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5, 5 + L_FEATURE_RANGE_TOLERANCE + 1);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertFalse(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}

test(FeatureManager_featureExists_ExitOutsideXYBoundRange)
{
	FeatureManager _featureManager;
	PatternManager _patternManager;
	Point startPoint(DATA);
	Point endPoint(DATA);
	//Entry
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit
	startPoint.setXY(5, 5);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
	//Entry 2nd feature
	startPoint.setXY(0, 0);
	endPoint.setXY(5, 5);
	_patternManager.addPattern(&startPoint, &endPoint);
	//Exit 2nd feature
	startPoint.setXY(5 + L_FEATURE_RANGE_TOLERANCE + 1, 5 + L_FEATURE_RANGE_TOLERANCE + 1);
	endPoint.setXY(10, 0);
	_patternManager.addPattern(&startPoint, &endPoint);
	DoublyLinkedNodeIterator<Feature> iter(*_featureManager.getFeatureList());
	iter++;
	assertFalse(_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()));
}
#endif