#include "ComsEncoder.h"

#define C_COMS_CODE_ACCGYRO 1


ComsEncoder::ComsEncoder(Coms* coms, Error *e) :_accGyro_man(e)
{
	_e = e;
	_coms = coms;
}

void ComsEncoder::run()
{
	if (_coms->canSend())
	{
		if (_connectRequest)
		{
			uint8_t toSend[] = { C_COMS_CODE_CONNECT_REQUEST };
			_coms->send(toSend, 1);
			_connectRequest = false;
		}
		if (!_accGyro_man.isEmpty())
		{
			int remoe = _accGyro_man.remove();
			_coms->send(_accGyro[remoe], 25);
		}
	}
}

void ComsEncoder::sendConnectRequest()
{
	_connectRequest = true;
}

void ComsEncoder::sendAccGyro(float accel[3], float gyro[3])
{

	if (_accGyro_man.isFull())
	{
		//@TODO notify of overflow
		return;
	}
	
	int toAdd = _accGyro_man.add();
	uint16_t buffer = (accel[0] * 1000);

	_accGyro[toAdd][0] = C_COMS_CODE_ACCGYRO;
	
	uint8_t *u_acc = reinterpret_cast<uint8_t *>(accel);
	for (int i = 0; i < (3*4); i++)
	{
		_accGyro[toAdd][1 + i] = u_acc[i];
	}

	uint8_t *u_gyro = reinterpret_cast<uint8_t *>(gyro);
	for (int i = 0; i < (3 * 4); i++)
	{
		_accGyro[toAdd][13 + i] = u_gyro[i];
	}

}
