#pragma once
#include "Error.h"

/**
* \brief	A Queue
*
* \tparam	T		The type of the object to add
* \tparam	Size	Size of the buffer
*/
template<class T, int Size>
class CircularBuffer
{
public:

	/**
	* \fn	CircularBuffer_Manager::CircularBuffer()
	*
	* \brief	Default constructor
	*/
	CircularBuffer(volatile Error *e)
	{
		_e = e;
		_start = 0;
		_end = 0;
		_size = 0;
	}

	/**
	* \fn	bool CircularBuffer::isEmpty()
	*
	* \brief	Query if this object is empty
	*
	* \return	true if empty, false if not
	*/
	bool isEmpty()
	{
		if (_size == 0)
		{
			return true;
		}
		return false;
	}

	/**
	* \fn	bool CircularBuffer::isFull()
	*
	* \brief	Query if this object is full
	*
	* \return	true if full, false if not
	*/
	bool isFull()
	{
		if (_size == Size)
		{
			return true;
		}
		return false;
	}

	/**
	* \brief	The number of objects in the buffer
	*
	* \return	The Size
	*/
	int size()
	{
		return _size;
	}

	/**
	* \brief	Adds a object to the buffer
	*
	* \param	toAdd	The object to add
	*
	* \throw	E_ILLEGAL_ACCESS	If full
	*/
	void add(T toAdd)
	{
		if (isFull())
		{
			_e->add(E_BUFFER_OVERFLOW, __LINE__);
			return;
		}
		_size++;

		int toRemove = _start;

		_start++;
		if (_start >= Size)
		{
			_start = 0;
		}

		_buffer[toRemove] = toAdd;
	}

	/**
	* \fn	int CircularBuffer_Manager::remove(Error *e)
	*
	* \brief	Removes an object from the buffer
	*
	* \throw	E_ILLEGAL_ACCESS	If full
	*
	* \return	The index of the object to remove
	*/
	T remove()
	{
		T empty;
		if (isEmpty())
		{
			_e->add(E_BUFFER_OVERFLOW, __LINE__);
			return empty;
		}

		_size--;

		int toRemove = _end;

		_end++;
		if (_end >= Size)
		{
			_end = 0;
		}

		return _buffer[toRemove];
	}

	T get(int i)
	{
		if (i >= _size)
		{
			return T();
		}
		int index = _end + i;
		if (index >= Size)
		{
			index -= _size;
		}
		return _buffer[index];
	}

private:

	/** \brief	The index to add to. */
	int _start;

	/** \brief	The index to remove from. */
	int _end;

	/** \brief	The system's error object */
	volatile Error *_e;

	/** \brief	The number of objects in the buffer */
	int _size;

	/** \brief	The Buffer */
	T _buffer[Size];
};
