#include "Coms.h"

Coms::Coms(volatile Error *e) :_comsDecoder(e)
{
	_sendCount = 0;
	_readCount = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Coms::getNORegisters()
{
	return _comsDecoder.getNORegisters();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

volatile MessageBuffer_Passer* Coms::getNextRegister()
{
	return _comsDecoder.getNextRegister();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Coms::send(volatile MessageBuffer_Passer* data)
{
	send((uint8_t*)data->getPacket(), data->getPacketSize());
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Coms::send(uint8_t *data, uint8_t length)
{
	COM_SERIAL.write(data, length);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Coms::run()
{
	// take a snapshot of the byte to prevent this locking if we receive more that we can process @TODO add overflow check 
	int readCount = COM_SERIAL.available();

	for (int i = 0; i < readCount; i++)
	{
		uint8_t read = COM_SERIAL.read();

		if (read == END_BYTE)
		{
			// remove the last byte from the checksum (it is the checksum)
			_checkSum -= _readMessage[_readCount - 1] * _readCount;
			if (_comsDecoder.processMessage(_readMessage, _readCount, _checkSum))
			{
				_readCount = 0;
				_checkSum = 0;
				return true;
			}
			else
			{
				_readCount = 0;
				_checkSum = 0;
				return false;
			}
		}
		else
		{
			if (_readCount < MAX_PACKET_SIZE)
			{
				_readMessage[_readCount] = read;
				_readCount++;
				_checkSum += read*_readCount;
			}
		}
	}
	return false;
}