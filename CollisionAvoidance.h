#pragma once

#include "CONFIG.h"
#include "MessageBuffer_Passer.h"
#include "MessageBuffer.h"

/**
* \class	CollisionAvoidance
*
* \brief	Cacualte the diferntion the drone shopuld travel to avoid obsiticals based on LIDAR data
*/
class CollisionAvoidance
{
public:
	CollisionAvoidance();

	/**
	* \brief	Add a new points, the compensation vector will not change untill after endOfSweep() is called
	*/
	void newPoint(double angle, double distance);

	/**
	* \brief	Called after the last point in the sweep, calculate the compensation vector for the last sweep
	*/
	void endOfSweep();

	// standard runnable methods
	virtual volatile MessageBuffer_Passer* getRegister(){ return &_CompensatorRegister; }
private:

	/** \brief	The sum of the xComponents of points in the safty circle */
	double _xComp;

	/** \brief	The sum of the yComponents of points in the safty circle */
	double _yComp;

	/** \brief	The closest point */
	double _minDistance;

	/** \brief	The compensation vector cacualted after every sweep */
	volatile MessageBuffer<MB_COMPENSATOR_VECTOR, 2> _CompensatorRegister;
};

