#pragma once

#include "RollingWindow.h"
#include "Point.h"

template<int Size>
class RollingCorrelation
{
public:

	RollingCorrelation(volatile Error *e) : _points(e)
	{
		_e = e;

		for (int i = 0; i < 2; i++)
		{
			_XMean[i] = 0;
			_YMean[i] = 0;
			_yx[i] = 0;
			_xx[i] = 0;
			_yy[i] = 0;
		}
	}

	void newPoint(Point p)
	{
		Point removed;

		// remove old points
		if (_points.isFull())
		{
			removed = _points.add(p);
			for (int i = 0; i < 2; i++)
			{
				_yx[i] -= (removed.getX(i)* removed.getY(i));
				_xx[i] -= (removed.getX(i)* removed.getX(i));
				_yy[i] -= (removed.getY(i)* removed.getY(i));
				_XMean[i] -= removed.getX(i);
				_YMean[i] -= removed.getY(i);
			}
		}
		else
		{
			removed = _points.add(p);
		}

		// add new points
		for (int i = 0; i < 2; i++)
		{
			_yx[i] += (p.getX(i)* p.getY(i));
			_xx[i] += (p.getX(i)* p.getX(i));
			_yy[i] += (p.getY(i)* p.getY(i));
			_YMean[i] += p.getY(i);
			_XMean[i] += p.getX(i);
		}

	}

	double getCorrelation()
	{
		if (!_points.isFull())
		{
			return  0; 
		}
		double c1 = getC(0);
		double c2 = getC(1);
		if (abs(c1) > abs(c2))
		{
			return c1;
		}
		else
		{
			return c2;
		}
	}

	Point getCenter()
	{
		return _points.get(Size / 2);
	}

private:

	double getAB(int i)
	{
		return _yx[i] - ((_XMean[i] * _YMean[i]) / _points.getSize());
	}

	double getAA(int i)
	{
		return _xx[i] - ((_XMean[i] * _XMean[i]) / _points.getSize());
	}

	double getBB(int i)
	{
		return _yy[i] - ((_YMean[i] * _YMean[i]) / _points.getSize());
	}

	double getC(int i)
	{
		return getAB(i) / sqrt(getAA(i)*getBB(i));
	}

	RollingWindow<Point, Size> _points;

	double _XMean[2];
	double _YMean[2];
	double _yx[2];
	double _xx[2];
	double _yy[2];

	volatile Error *_e;
};

