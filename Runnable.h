#pragma once
#include "MessageBuffer_Passer.h"

class Runnable
{
public:
	virtual int getNORegisters() = 0;
	virtual volatile MessageBuffer_Passer* getRegister() = 0;
	virtual void addRegister(volatile MessageBuffer_Passer* newRegister) = 0;

	virtual bool start()  = 0;
	virtual bool run() = 0;
};

