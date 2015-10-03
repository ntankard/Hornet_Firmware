#include "Coms.h"

Coms::Coms()
{
	_sendCount = 0;

	_pendingMessageDefault.setID(0xff);
	_pendingMessage = &_pendingMessageDefault;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Coms::send(volatile MessageBuffer_Passer* data)
{
	send((uint8_t*)data->getPacket(), data->getPacketSize());
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Coms::send(uint8_t *data, uint8_t length)
{
	uint8_t checkSum = 0;
	int sendId = 1;

	// langth of the data (payload (ID and payload))
	COM_SERIAL.write(length);
	checkSum += (sendId * length);
	sendId++;

	// send count for packet loss on the receiver side
	COM_SERIAL.write(_sendCount);
	checkSum += (sendId * _sendCount);
	sendId++;

	// packet payload (ID and payload)
	for (int i = 0; i < length;i++)
	{
		COM_SERIAL.write(data[i]);
		checkSum += (data[i] * sendId);
		sendId++;
	}

	// cumulative checksum
	COM_SERIAL.write(checkSum);

	// cut the end of the packet
	COM_SERIAL.write(END_BYTE);

	_sendCount++;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Coms::run()
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

			if (_readCount <= 3)
			{
				// packet is imposibly small
			}
			else if (_readCount != (_readMessage[0] + 3))
			{
				// packet is the wrong side
			}
			else if (_checkSum != _readMessage[_readCount - 1])
			{
				// checksum fail
			}
			else
			{
				// valid paket
				_pendingMessage = _comsDecoder.processMessage(_readMessage, _readCount);

				_readCount = 0;
				_checkSum = 0;

				return 1;
			}

			_readCount = 0;
			_checkSum = 0;
			return 0;
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
	return 0;
}