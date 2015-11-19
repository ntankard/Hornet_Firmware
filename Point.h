#pragma once 

#include "math.h"

/**
* \class	Point
*
* \brief	A lidar point in both polar and rectangular form (at the original angle and 45 degrees)
*
* \note		2 rectangulare versions of the point( one sshifted by 45 degrees) are stored becuase straight vertical lines break the rolling corelation so the offset one can be used to check for this
*/
class Point
{
public:

	Point();
	void setPolar(double angle, double distance);
	double getAngle() const;
	double getDistance() const;

	/**
	* \brief	Gets the x coord of the rectangular form of the point
	*
	* \param	i	Wich of the 2 points to get (i==0 is for the origianl point)(i!=0 is for the point shifted by 45 degrees)
	*
	* \return	line	The X cord of the point
	*/
	double getX(int i = 0) const;

	/**
	* \brief	Gets the y coord of the rectangular form of the point
	*
	* \param	i	Wich of the 2 points to get (i==0 is for the origianl point)(i!=0 is for the point shifted by 45 degrees)
	*
	* \return	line	The y cord of the point
	*/
	double getY(int i = 0) const;
	
private:

	/** \brief	The angle of the point */
	double _angle;

	/** \brief	The distance from the center */
	double _distance;

	/** \brief	The x component of the rectangular form of the point */
	double _coorX;

	/** \brief	The y component of the rectangular form of the point */
	double _coorY;

	/** \brief	The x component of the rectangular form of the point shifted by 45 */
	double _coorX_S;

	/** \brief	The y component of the rectangular form of the point shifted by 45 */
	double _coorY_S;
};