#pragma once

#if BUILD_TYPE == FOR_TEST

#include "PatternManager.h"

test(PatternManager_Setup)
{
	PatternManager* _patternManager = new PatternManager();
}

#endif