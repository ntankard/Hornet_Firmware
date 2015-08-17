#include "ComsEncoder.h"

#define C_COMS_CODE_ACCGYRO 1


ComsEncoder::ComsEncoder(Coms* coms, Error *e) :_accGyro_man(e), _messageBuffer_man(e)
{
	_e = e;
	_coms = coms;
}

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

		//priority 2 (non critical nav data)
		if (!_accGyro_man.isEmpty())
		{
			int remoe = _accGyro_man.remove();
			_coms->send(_accGyro[remoe], 25);
			return;
		}
	}
}

void ComsEncoder::sendChar(uint8_t message)
{
	if (_messageBuffer_man.isFull())
	{
		//@TODO notify of overflow
		return;
	}

	_messageBuffer[_messageBuffer_man.add()] = message;
}

void ComsEncoder::sendAccGyro(float accel[3], float gyro[3])
{

	if (_accGyro_man.isFull())
	{
		//@TODO notify of overflow
		return;
	}
	
	int toAdd = _accGyro_man.add();

	_accGyro[toAdd][0] = C_COMS_CODE_ACCGYRO;
	
	uint8_t *u_acc = reinterpret_cast<uint8_t *>(accel);
	int addCount = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_accGyro[toAdd][addCount] = u_acc[((4*(i+1))-1)-j];
			addCount++;
		}
	}

	uint8_t *u_gyro = reinterpret_cast<uint8_t *>(gyro);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_accGyro[toAdd][addCount] = u_gyro[((4 * (i + 1)) - 1) - j];
			addCount++;
		}
	}
}
