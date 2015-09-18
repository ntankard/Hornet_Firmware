#include "ComsEncoder.h"

ComsEncoder::ComsEncoder( volatile Error *e)
{
	_e = e;

	// make the buffers safe
	for (int i = 0; i < C_CL; i++)
	{
		_buffer_man[i].setError(e);
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int ComsEncoder::run()
{
	if (_coms.canSend())
	{
		// priority 1 (messages)
		if (!_messageBuffer_man.isEmpty())
		{
			uint8_t toSend[] = { _messageBuffer[_messageBuffer_man.remove()] };
			_coms.send(toSend, 1);
		}

		for (int i = 0; i < C_CL; i++)
		{
			if (!_buffer_man[i].isEmpty())
			{
				int sendLoc = _buffer_man[i].remove();
				volatile MessageBuffer_Passer* toSend = _buffer[i][sendLoc];
				_coms.send((uint8_t*)toSend->getPacket(), toSend->getPacketSize());
				toSend->unlock();
				break;
			}
		}
	}

	if (_coms.run() != 0)
	{
		_toReturn = _coms.getMessage();
		return 1;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ComsEncoder::sendData(volatile MessageBuffer_Passer *data)
{
	if (_buffer_man[data->getComPri()].isFull())
	{
		return false;
	}

	if (data->isLocked())
	{
		return false;
	}
	int addLoc = _buffer_man[data->getComPri()].add();
	_buffer[data->getComPri()][addLoc] = data;

	data->lock();

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ComsEncoder::sendChar(uint8_t message)
{
	if (_messageBuffer_man.isFull())
	{
		return false;
	}

	_messageBuffer[_messageBuffer_man.add()] = message;
	return true;
}