#pragma once

#if BUILD_TYPE == FOR_TEST

#include "Error.h"
#include "Point.h"

test(Pattern_Starts_Empty)
{
	Error e;
	Pattern pattern();

	//Check point is made correctly
	assertTrue(pattren.isEmpty());
}

#endif;