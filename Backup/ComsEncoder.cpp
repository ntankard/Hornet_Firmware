#include "ComsEncoder.h"

ComsEncoder::ComsEncoder(Coms* coms, Error *e)
{
	_e = e;
	_coms = coms;

	// make the buffers safe
	for (int i = 0; i < C_CL; i++)
	{
		_buffer_man[i].setError(e);
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ComsEncoder::run()
{
	if (_coms->canSend())
	{
		// priority 1 (messages)
		if (!_messageBuffer_man.isEmpty())
		{
			uint8_t toSend[] = { _messageBuffer[_messageBuffer_man.remove()] };
			_coms->send(toSend, 1);
			return;
		}

		for (int i = 0; i < C_CL; i++)
		{
			if (!_buffer_man[i].isEmpty())
			{
				int sendLoc = _buffer_man[i].remove();
				MessageBuffer_Passer* toSend = _buffer[i][sendLoc];
				_coms->send(toSend->getPacket(), toSend->getPacketSize());
				toSend->unlock();
				return;
			}
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ComsEncoder::sendData(MessageBuffer_Passer *data)
{
	if (_buffer_man[data->getComPri()].isFull())
	{
		return false;
	}

	int addLoc = _buffer_man[data->getComPri()].add();
	_buffer[data->getComPri()][addLoc] = data;
	if (data->isLocked())
	{
		return false;
	}
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