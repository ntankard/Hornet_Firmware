#pragma once
#include "Coms.h"

class ComsEncoder
{
public:
	ComsEncoder(Coms* coms);

	void run();

private:
	Coms *_coms;
};

