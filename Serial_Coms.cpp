#include "Serial_Coms.h"

#if COM_MODE == COM_MODE_SERIAL

Serial_Coms::Serial_Coms(ComsDecoder* comsDecoder) :Coms(comsDecoder)
{
	C_COMS_PORT.begin(C_COMS_BAUD_RATE);
	_readData = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serial_Coms::run()
{
	while (C_COMS_PORT.available())	// keep reading untill a full packet has been read
	{
		uint8_t read = C_COMS_PORT.read();
		if (read == '\n')
		{
			_comsDecoder->processMessage(_buffer, _readData);
			_readData = 0;
			break;
		}
		else
		{
			_buffer[_readData] = read;
			_readData++;
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Serial_Coms::canSend()
{
	return true;	// there is no way to check if a message was sent sucsesfuly
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Serial_Coms::send(uint8_t *data, uint8_t dataLength)
{
	for (int i = 0; i < dataLength; i++)
	{
		C_COMS_PORT.write(data[i]);
	}
	C_COMS_PORT.write("\n");
}
#endif