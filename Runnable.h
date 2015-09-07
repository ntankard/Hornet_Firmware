#pragma once
#include "MessageBuffer_Passer.h"

class Runnable
{
public:
	virtual bool start()=0;
	virtual int run() = 0;
	virtual MessageBuffer_Passer* getMessage();
};

