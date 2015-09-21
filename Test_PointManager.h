#pragma once

#if BUILD_TYPE == FOR_TEST

#include "PointManager.h"

test(PointManager_Setup)
{
	PointManager* _pointManager = new PointManager();
}

#endif