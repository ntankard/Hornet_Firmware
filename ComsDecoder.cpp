#include "ComsDecoder.h"
#include "Arduino.h"
#include "CONFIG.h"
#include "HornetManager.h"

ComsDecoder::ComsDecoder(volatile Error *e)
{
	_e = e;
	_registerAccsessed = 0;

	int addCount = 0;
	_registers[MB_JOY_THROTTLE - MB_INBOUND_OFFSET] = &_throttleJoyRegister;
	addCount++;
	_registers[MB_JOY_XY - MB_INBOUND_OFFSET] = &_XYJoyRegister;
	addCount++;
	_registers[MB_JOY_Z - MB_INBOUND_OFFSET] = &_ZJoyRegister;
	addCount++;
	_registers[MB_ARM_DISARM - MB_INBOUND_OFFSET] = &_ArmDisarmRegister;
	addCount++;
	_registers[MB_AVOID - MB_INBOUND_OFFSET] = &_AvoidRegister;
	addCount++;

	if (addCount != MB_INBOUND_COUNT)
	{
		_e->add(E_NULL_PTR, __LINE__);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

int ComsDecoder::getNORegisters()
{
	return MB_INBOUND_COUNT;
}

//-----------------------------------------------------------------------------------------------------------------------------

volatile MessageBuffer_Passer* ComsDecoder::getNextRegister()
{
	volatile MessageBuffer_Passer* toReturn = _registers[_registerAccsessed];

	_registerAccsessed++;
	if (_registerAccsessed >= MB_INBOUND_COUNT)
	{
		_registerAccsessed = 0;
	}

	return toReturn;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool ComsDecoder::processMessage(uint8_t *data, uint8_t dataLength, uint8_t checksum)
{
	uint8_t arrayID = data[2] - MB_INBOUND_OFFSET;
	if (arrayID < MB_INBOUND_COUNT)
	{
		if (!_registers[arrayID]->setPacket(data, dataLength, checksum))
		{
			// corrupt packet
			return false;
		}
	}
	else
	{
		// corrupt packet
		return false;
	}
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

void ComsDecoder::sendFailure()
{
	//@TODO monitor this
}

//-----------------------------------------------------------------------------------------------------------------------------

void ComsDecoder::receiveFailure()
{
	//@TODO monitor this
}