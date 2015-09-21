#pragma once

#include "LidarNavigation.h"
#include "math.h"
#include "Pattern.h"


LidarNavigation::LidarNavigation(HornetManager *theHornetManager, Error *theError)
{
	_e = theError;
	_hornetManager = theHornetManager;
}

LidarNavigation::LidarNavigation()
{
	_pointManager = new PointManager();
	_patternManager = new PatternManager();
	// _featureManager = new FeatureManager();
	// _anchorManager = new AnchorManager();
}

void LidarNavigation::processLidarData(float angle, float distance)
{/*
	_pointManager->addPoint(angle, distance);
	if (_pointManager->isPattern())
	{
		_patternManager->addPattern(_pointManager->getStartPoint(), _pointManager->getEndPoint());
		if (_patternManager->isFeature())
		{
			_featureManager->addFeature(_patternManager->getEntryPattern(), _patternManager->getExitPattern());
			if (_featureManager->isAnchor())
			{
				_anchorManager->addAnchor(_featureManager->getRecurringFeature());
			}
		}
	}*/
}