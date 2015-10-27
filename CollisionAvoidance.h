#pragma once

#include "CONFIG.h"
#include "MessageBuffer_Passer.h"
#include "MessageBuffer.h"

class CollisionAvoidance
{
public:
	CollisionAvoidance();

	void newPoint(double angle, double distance);

	void endOfSweep();

	virtual volatile MessageBuffer_Passer* getRegister(){ return &_CompensatorRegister; }
private:
	double _xComp;
	double _yComp;
	double _minDistance;


	volatile MessageBuffer<MB_COMPENSATOR_VECTOR, 2> _CompensatorRegister;
};

