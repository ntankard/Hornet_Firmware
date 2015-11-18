#pragma once

#include "Error.h"
#include "AnchorDetector.h"
#include "AnchorManager.h"

class LidarNavigation
{
public:
	LidarNavigation(volatile Error* e);
	void processLidarData(double angle, double distance);
	void endOfSweep();
	volatile MessageBuffer_Passer* getNextRegister()
	{
		return _anchorManager.getNextRegister();
	}
private:
	AnchorManager _anchorManager;
	//AnchorDetector _anchorDetector;
};

