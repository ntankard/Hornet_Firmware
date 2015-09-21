#include "Serial_Coms.h"
#include "Arduino.h"

#ifdef USER_SERIAL_COMS

Coms::Coms()
{
	//C_COMS_PORT.begin(C_COMS_BAUD_RATE);
	_readData = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Coms::run()
{
	while (C_SERIAL_COMS_PORT.available())	// keep reading untill a full packet has been read
	{
		uint8_t read = C_SERIAL_COMS_PORT.read();
		if (read == '\n')
		{
			_pendingMessage = _comsDecoder.processMessage(_buffer, _readData);
			_readData = 0;
			return 1;
		}
		else
		{
			_buffer[_readData] = read;
			_readData++;
		}
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Coms::canSend()
{
	return true;	// there is no way to check if a message was sent sucsesfuly
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Coms::send(uint8_t *data, uint8_t dataLength)
{
	for (int i = 0; i < dataLength; i++)
	{
		C_SERIAL_COMS_PORT.write(data[i]);
	}
	C_SERIAL_COMS_PORT.write("\n");
}
#endif