#pragma once

#include "CircularBuffer.h"

/**
* \brief	A Moving window average
*
* \tparam	T		The type of the object
* \tparam	Size	Size of the Window
*/
template<class T, int Size>
class MovingAverage
{
public:

	/**
	* \brief	Default constructor.
	*
	* \param	e	The shared error object
	*/
	MovingAverage(Error *e) :_window(e)
	{
		_e = e;
		_sum = 0;
	}

	/**
	* \brief	Adds a object to the window (or shift the window)
	*
	* \param	toAdd	The object to add
	*/
	T add(T toAdd)
	{

		if (_window.isFull())
		{
			// full window
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

	/** \brief	The Window */
	CircularBuffer<T, Size> _window;

	/** \brief	The sum of all elemnts int the wondow */
	T _sum;

	/** \brief	The systems error object */
	Error *_e;
};

