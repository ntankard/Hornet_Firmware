#pragma once

#include "Line.h"
#include "math.h"

/**
* \class	Anchor
*
* \brief	A solid point in the LIDAR data to get position from, baesd on the interncection of 2 features
*/
class Anchor
{
public:
	Anchor();
	void setLines(Line start, Line end);
	Line getStart(){ return _start; };
	Line getEnd(){ return _end; }

	/**
	* \brief	Gets the solid point at the intercection between 2 anchors
	*
	* \return	The point at the center
	*/
	Point getAnchorPoint();
private:

	/** \brief	The first feature */
	Line _start;

	/** \brief	The second feature */
	Line _end;

	/** \brief	Is the anchor at the end of the start line or the end of the end line */
	bool _isInvert;
};

