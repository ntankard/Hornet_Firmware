#include "AnchorDetector.h"
#include "Arduino.h"

AnchorDetector::AnchorDetector(volatile Error *e) : _lineDetector(e)
{
	_count = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool AnchorDetector::newPoint(Point p)
{
	bool found = false;
	if (_lineDetector.newPoint(p))
	{
		Line toTest = _lineDetector.getLast();
		if (_count != 0)
		{
			double a = _last.getAngle();
			double b = toTest.getAngle();

			a += 180;
			b += 180;
			double dif = abs(a - b);

			if (dif > C_MIN_ANGLE && dif < C_MAX_ANGLE)
			{
				// new anchor
				_lastAnchor.setLines(_last, toTest);
				found = true;

			}
		}

		_last = toTest;
		_count++;
	}
	return found;
}

//-----------------------------------------------------------------------------------------------------------------------------

Anchor AnchorDetector::getLast()
{
	return _lastAnchor;
}


