#include "ComsEncoder.h"

ComsEncoder::ComsEncoder(volatile Error *e) :_coms(e)
{
	_e = e;

	_sendId = 0;
	for (int i = 0; i < MB_OUTBOUND_COUTN; i++)
	{
		_internalRegisters[i] = &_empty[i];
		_internalRegisters_addCount[i] = false;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int ComsEncoder::getNORegisters()
{
	return _coms.getNORegisters();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

volatile MessageBuffer_Passer* ComsEncoder::getRegister()
{
	return _coms.getNextRegister();
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ComsEncoder::addRegister(volatile MessageBuffer_Passer* newRegister)
{
	uint8_t ID = newRegister->getID() - MB_OUTBOUND_OFFSET;
	if (ID < MB_OUTBOUND_COUTN)
	{
		_internalRegisters_addCount[ID] = true;
		_internalRegisters[ID] = newRegister;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ComsEncoder::start()
{
	for (int i = 0; i < MB_OUTBOUND_COUTN; i++)
	{
		if (!_internalRegisters_addCount[i])
		{
			return false;	// not all registers have been attached
		}	
		if (_internalRegisters[i]->getID() == 0)
		{
			return false;
		}
	}
	_throttle.start(1);
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ComsEncoder::run()
{
	if (_throttle.hasTimeOut())
	{
		_throttle.start(1);
		// resend one of the packets
		_coms.send(_internalRegisters[_sendId]);
		_sendId++;
		if (_sendId >= MB_OUTBOUND_COUTN)
		{
			_sendId = 0;
		}
	}

	// attempt to read any packets
	return _coms.run();
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