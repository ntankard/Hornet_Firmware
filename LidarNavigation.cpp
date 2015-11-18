#include "LidarNavigation.h"


LidarNavigation::LidarNavigation(volatile Error* e) : _anchorManager(e)
{
}


void LidarNavigation::processLidarData(double angle, double distance)
{
	Point toAdd;

	angle = 360 - angle;

	toAdd.setPolar(angle, distance);
	_anchorManager.newPoint(toAdd);
}

void LidarNavigation::endOfSweep()
{

}