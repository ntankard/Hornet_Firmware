#include "LidarNavigation.h"


LidarNavigation::LidarNavigation(HornetManager *theHornetManager, Error *theError)
{
	_e = theError;
	_hornetManager = theHornetManager;
}

void LidarNavigation::newLidarPoint(float angle, float distance)
{
	// feature recognition here
	Point* point = new Point(angle, distance);

}

void LidarNavigation::EOSweep(float pitch, float roll, float yaw)
{
	// compare sweeps, look for ancors
}
