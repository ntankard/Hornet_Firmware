#pragma once

#include "RollingCorrelation.h"
#include "Line.h"
#include "CONFIG.h"

/**
* \class	LineDetector
*
* \brief	Calculate what parts of the LIDAR data are part of a straight line
*/
class LineDetector
{
public:
	LineDetector(volatile Error *e);
	bool newPoint(Point p);

	/**
	* \brief	Gets the last line found
	*/
	Line getLast();
private:

	/** \brief	Is the current section of data part of an ongoing line? */
	bool _isLine;

	/** \brief	Is the correlation positive? */
	bool _isPos;
	RollingCorrelation<C_CORRELATION_SIZE> _detector;

	/** \brief	The first point in the ongoing line */
	Point _start;
	Point _end;

	/** \brief	The last sucsesful line */
	Line _lastLine;

	/** \brief	The number of points in the line */
	int _num;
};

