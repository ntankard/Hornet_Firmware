#pragma once

#include "MessageBuffer_Passer.h"

template<int Size>
class MessageBuffer : public MessageBuffer_Passer
{
public:

	typedef union MemoryMap
	{
		struct
		{
			uint8_t data[Size * sizeof(float)];
		}raw;
		struct
		{
			float data[Size];
		}value;
	};

	//-----------------------------------------------------------------------------------------------------------------------------

	MessageBuffer(){}

	//-----------------------------------------------------------------------------------------------------------------------------

	float* getData()
	{
		return _message.value.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void setData(float* data)
	{
		for (int i = 0; i < Size; i++)
		{
			_message.value.data[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	uint8_t* getBytes()
	{
		return _message.raw.data;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	void setBytes(uint8_t* data)
	{
		for (int i = 0; i < (Size *sizeof(double)); i++)
		{
			_message.raw.data[i] = data[i];
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------

	int getSize()
	{
		return Size;
	}

	//-----------------------------------------------------------------------------------------------------------------------------

private:
	MemoryMap _message;
};

/*
template<class T, int Size>
class MessageBuffer
{
public:

	typedef union MemoryMap
	{
		struct
		{
			uint8_t data[Size * sizeof(T)];
		}raw;
		struct
		{
			T data[Size];
		}value;
	};

	MessageBuffer(int ID)
	{
		_ID = ID;
		_isLocked = false;
	}

	void setMessage(int i, T toAdd)
	{
		_message.value.data[i] = toAdd;
		_isLocked = true;
	}

	void setMessage(T toAdd[Size])
	{
		for (int i = 0; i < Size; i++)
		{
			setMessage(i, toAdd[i]);
		}
	}

	bool isLocked()
	{
		return _isLocked;
	}

	void free()
	{
		_isLocked = false;
	}

	T* getMessage()
	{
		return _message.value.data;
	}

	uint8_t* getBytes()
	{
		return _message.raw.data;
	}

	int getID()
	{
		return _message.value.ID;
	}

private:
	MemoryMap _message;
	int _ID;

	bool _isLocked;
};

*/