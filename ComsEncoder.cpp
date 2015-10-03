#include "ComsEncoder.h"

ComsEncoder::ComsEncoder( volatile Error *e)
{
	_e = e;

	_sendId = 0;
	for (int i = 0; i < MB_OUTBOUND_COUTN; i++)
	{
		_default[i].setID(0xff);
		_buffer[i] = &(_default[i]);
	}

	_toReturnDefault.setID(0xff);
	_toReturn = &_toReturnDefault;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int ComsEncoder::run()
{
	// resend one of the packets
	_coms.send(_buffer[_sendId]);
	_sendId++;
	if (_sendId >= MB_OUTBOUND_COUTN)
	{
		_sendId = 0;
	}
	

	// attempt to read any packets
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
	// check for valid pacekts
	if (data->getID() >= MB_OUTBOUND_COUTN)
	{
		return false;
	}

	// swich over the data
	_buffer[data->getID()]->unlock();
	_buffer[data->getID()] = data;
	_buffer[data->getID()]->lock();

	// send the data once
	_coms.send(data);

	return true;
}
















/*for (int i = 0; i < MB_OUTBOUND_COUTN; i++)
{
_coms.send((uint8_t*)_buffer[i]->getPacket(), _buffer[i]->getPacketSize());
}*/

// make the buffers safe
/*for (int i = 0; i < C_CL; i++)
{
_buffer_man[i].setError(e);
}*/

// priority 1 (messages)
/*if (!_messageBuffer_man.isEmpty())
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
}*/

	/*if (_buffer_man[data->getComPri()].isFull())
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

	return true;*/


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
bool ComsEncoder::sendChar(uint8_t message)
{
	if (_messageBuffer_man.isFull())
	{
		return false;
	}

	_messageBuffer[_messageBuffer_man.add()] = message;
	return true;
}
*/