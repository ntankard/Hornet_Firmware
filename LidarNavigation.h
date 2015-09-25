#pragma once

#include "HornetManager.h"
#include "Error.h"
#include "PointManager.h"
#include "PatternManager.h"
#include "FeatureManager.h"
#include "AnchorManager.h"

class LidarNavigation
{
public:
	LidarNavigation();
	void processLidarData(float angle, float distance);
	void EOSweep(float pitch, float roll, float yaw);
private:

	PointManager _pointManager;
	PatternManager _patternManager;
	FeatureManager _featureManager;
	AnchorManager _anchorManager;
};


