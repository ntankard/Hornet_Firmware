#include "AnchorDetector.h"


AnchorDetector::AnchorDetector(volatile Error *e) : _lineDetector(e)
{
	_count = 0;
}

bool AnchorDetector::newPoint(Point p)
{
	bool found = false;
	if (_lineDetector.newPoint(p))
	{
		Line toTest = _lineDetector.getLast();
		if (_count != 0)
		{
			float a = _last.getAngle();
			float b = toTest.getAngle();

			a += 180;
			b += 180;
			float dif = abs(a - b);

			if (dif > C_MIN_ANGLE && dif < C_MAX_ANGLE)
			{
				// new ancor
				_lastAnchor.setLines(_last, toTest);
				found = true;
			}
		}

		_last = toTest;
		_count++;
	}
	return found;
}

Anchor AnchorDetector::getLast()
{
	return _lastAnchor;
}


