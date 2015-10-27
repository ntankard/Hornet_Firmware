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
	//_throttle.start(1);
	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ComsEncoder::run()
{
	//if (_throttle.hasTimeOut())
	//{
		//_throttle.start(1);
		// resend one of the packets
		_coms.send(_internalRegisters[_sendId]);
		_sendId++;
		if (_sendId >= MB_OUTBOUND_COUTN)
		{
			_sendId = 0;
		}
	//}

	/*for (int i = 0; i < MB_OUTBOUND_COUTN; i++)
	{
		_coms.send(_internalRegisters[i]);
	}*/

	// attempt to read any packets
	return _coms.run();
}