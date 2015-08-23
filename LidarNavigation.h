#pragma once

#include "HornetManager.h"
#include "Error.h"
#include "DoublyLinkedNodeIterator.h"
#include "Point.h"

class LidarNavigation
{
public:
	LidarNavigation(HornetManager *theHornetManager, Error *theError);

	void newLidarPoint(float angle, float distance);

	void EOSweep(float pitch, float roll, float yaw);

private:

	HornetManager *_hornetManager;
	Error *_e;
};


