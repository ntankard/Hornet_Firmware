#include "Coms.h"



Coms::Coms()
{
	_sendCount = 0;
}

void Coms::send(uint8_t *data, uint8_t length)
{
	uint8_t checkSum = 0;
	int sendId = 1;

	COM_SERIAL.write(length);
	checkSum += (sendId * length);
	sendId++;

	for (int i = 0; i < length;i++)
	{
		COM_SERIAL.write(data[i]);
		checkSum += (data[i] * length);
		sendId++;
	}

	COM_SERIAL.write(checkSum);

	COM_SERIAL.write(END_BYTE);

	_sendCount++;
}

int Coms::run()
{
	int readCount = COM_SERIAL.available();

	for (int i = 0; i < readCount; i++)
	{
		uint8_t read = COM_SERIAL.read();

		if (read == END_BYTE)
		{
			// end of a packet
			if (_readCount <= 4)
			{
				// corupt packet
				TP("PACKET TO SMALL");
			}
			else if (_readCount != (_readMessage[2] + 4))
			{
				// corupt packet
				TP("Count mismatch");
			}
			else if (_checkSum != _readMessage[_readCount - 1])
			{
				// corupt packet
				TP("Checksum fail");
			}
			else
			{
				// valid paket
				_pendingMessage = _comsDecoder.processMessage(_readMessage, _readCount);
				TP("Valid packet");
			}




			_readCount = 0;
			_checkSum = 0;
			break;
		}
		else
		{
			if (_readCount >= MAX_PACKET_SIZE)
			{
				// packet overflow
			}

			// part of a packet
			_readMessage[_readCount] = read;
			_readCount++;
			_checkSum += read*_readCount;
		}
	}
}
bool Coms::canSend()
{
	return true;	// there is no way to check if a message was sent sucsesfuly
}