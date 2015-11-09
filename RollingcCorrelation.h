#pragma once

//#include "CircularBuffer.h"
#include "RollingWindow.h"
#include "Point.h"

template<int Size>
class RollingCorrelation
{
public:

	RollingCorrelation(volatile Error *e) : _points(e)
	{
		_e = e;

		_XMean=0;
		_YMean=0;

		_ab_yx=0;
		_ab_xmy=0;
		_ab_ymx=0;
		_ab_mxmy=0;
	}

	void newPoint(Point p)
	{
		float pastSize = _points.getSize();
		float pastXMean = _XMean;
		float pastYMean = _YMean;

		if (pastSize != 0)
		{
			_XMean /= pastSize;
			_YMean /= pastSize;
		}

		if (_points.isFull())
		{
			Point removed = _points.add(p);
			_ab_yx -= (removed.getX()* removed.getY());
			_ab_xmy -= removed.getX()*pastYMean;
			_ab_ymx -= removed.getY()*pastXMean;
			_ab_mxmy -= _XMean*_YMean;
			_XMean -= removed.getX();
			_YMean -= removed.getY();
		}

		Point removed = _points.add(p);

		_YMean += p.getY();
		_XMean += p.getX();
		TP((String)_YMean);
		_YMean *= _points.getSize();
		_XMean *= _points.getSize();
		TP((String)_points.getSize());

		_ab_yx += (p.getX()* p.getY());

		if (pastYMean != 0)
		{
			_ab_xmy = _ab_xmy / pastYMean;
		}
		if (pastYMean != 0)
		{
			_ab_ymx = _ab_ymx / pastXMean;
		}
		_ab_xmy += p.getX();
		_ab_ymx += p.getY();
		_ab_xmy = _ab_xmy * _YMean;
		_ab_ymx = _ab_ymx * _XMean;

		_ab_mxmy += _YMean * _XMean;

		TP("_ab_yx: " + (String)_ab_yx);
		TP("_ab_ymx: " + (String)_ab_ymx);
		TP("_ab_xmy: " + (String)_ab_xmy);
		TP("_ab_mxmy: " + (String)_ab_mxmy);

		TP("AB: " + (String)(_ab_yx - _ab_ymx - _ab_xmy - _ab_mxmy));
	}

private:

	//RollingWindow<float, Size> _a;
	//RollingWindow<float, Size> _b;

	RollingWindow<Point, Size> _points;

	float _XMean;
	float _YMean;

	float _ab_yx;
	float _ab_xmy;
	float _ab_ymx;
	float _ab_mxmy;



	//RollingWindow<float, Size> _yMean;

	//RollingWindow<float, Size> _ab;


	//RollingWindow<float, Size> _aa;
	//RollingWindow<float, Size> _bb;

	
	/** \brief	The systems error object */
	volatile Error *_e;
};

