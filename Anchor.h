#pragma once 
#include "Feature.h"

class Anchor
{
public:
	Anchor(Feature* feature)
	{
		_feature = feature;
	}
private:
	Feature* _feature;
};