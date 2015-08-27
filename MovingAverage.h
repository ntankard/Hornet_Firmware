#pragma once

#include "CircularBuffer.h"

template<class T, int Size>
class MovingAverage
{
public:
	MovingAverage(Error *e) :_window(e)
	{
		_e = e;
	}

	T add(T toAdd)
	{
		if (_window.isFull())
		{
			_sum -= _window.remove();
			_sum += toAdd;
			_window.add(toAdd);

			return _sum / ((float)_window.size());
		}
		else
		{
			if (_window.isEmpty())
			{
				// first time
				_sum = toAdd;
				_window.add(toAdd);
				return toAdd;
			}
			else
			{
				// filling up
				_sum += toAdd;
				_window.add(toAdd);

				return _sum/((float)_window.size());
			}
		}
	}
	
private:
	CircularBuffer<T, Size> _window;
	T _sum;
	Error *_e;
};

