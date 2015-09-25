#pragma once

#include "LidarNavigation.h"
#include "math.h"
#include "Pattern.h"


LidarNavigation::LidarNavigation()
{

}

void LidarNavigation::processLidarData(float angle, float distance)
{
	_pointManager.addPoint(angle, distance);
	if (_pointManager.isPattern())
	{
		_patternManager.addPattern(_pointManager.getStartPoint(), _pointManager.getEndPoint());
		if (_patternManager.isFeature())
		{
			if (!_featureManager.featureExists(_patternManager.getEntryPattern(), _patternManager.getExitPattern()))
			{
				_featureManager.addFeature(_patternManager.getEntryPattern(), _patternManager.getExitPattern());
			}
			else if (_featureManager.isAnchor())
			{
				_anchorManager.addAnchor(_featureManager.getReccuringFeature());
			}
		}
	}
}

void LidarNavigation::EOSweep(float pitch, float roll, float yaw)
{
	_featureManager.manageFeatureList();
}