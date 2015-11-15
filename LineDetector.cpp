#include "LineDetector.h"


LineDetector::LineDetector(volatile Error *e) : _detector(e)
{
	_isLine = false;
}

bool LineDetector::newPoint(Point p)
{
	_detector.newPoint(p);
	_num++;
	float cor = _detector.getCorrelation();
	if (!_isLine)
	{
		if (abs(cor) >= C_THRESHOLD)
		{
			if (cor > 0)
			{
				_isPos = true;
			}
			else
			{
				_isPos = false;
			}
			// start line

			_num = 0;
			_start = _detector.getCenter();

			_isLine = true;
		}
	}
	else
	{
		if (!(_isPos && cor >= C_THRESHOLD) && !(!_isPos && cor <= -C_THRESHOLD))	// drop below threshold or swich sign
		{
			// end line
			if (_num >= C_MIN_SIZE)
			{
				_end = _detector.getCenter();
				_isLine = false;
				_lastLine.setPoints(_start, _end);
				return true;
			}


			_isLine = false;
		}
	}
	return false;
}

Line LineDetector::getLast()
{
	return _lastLine;
}

