#pragma once

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
			
		}
		else
		{
			if (_window.isEmpty())
			{
				// first time
				_sum = toAdd;
				_window.add(toAdd);
			}
			else
			{
				// filling up
				_sum += toAdd;
				_window.add(toAdd);

				return _sum;
			}
		}
	}
	
private:
	CircularBuffer<T, Size> _window;
	T _sum;
	Errorr *_e;
};

