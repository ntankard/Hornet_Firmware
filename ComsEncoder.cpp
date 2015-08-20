#include "ComsEncoder.h"

ComsEncoder::ComsEncoder(Coms* coms, Error *e) :_rawAccGyro_man(e), _messageBuffer_man(e), _pitchRoll_man(e), _lidarData_man(e)
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
		if (!_rawAccGyro_man.isEmpty())
		{
			int remove = _rawAccGyro_man.remove();
			_coms->send(_rawAccGyro[remove], 25);
			return;
		}

		if (!_pitchRoll_man.isEmpty())
		{
			int remove = _pitchRoll_man.remove();
			_coms->send(_pitchRoll[remove], 9);
			return;
		}
		
		if (!_lidarData_man.isEmpty())
		{
			int remove = _lidarData_man.remove();
			_coms->send(_lidarData[remove], 9);
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

void ComsEncoder::sendRawAccGyro(float accel[3], float gyro[3])
{

	if (_rawAccGyro_man.isFull())
	{
		//@TODO notify of overflow
		return;
	}
	
	int toAdd = _rawAccGyro_man.add();

	_rawAccGyro[toAdd][0] = C_COMS_CODE_ACCGYRO;
	
	uint8_t *u_acc = reinterpret_cast<uint8_t *>(accel);
	int addCount = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_rawAccGyro[toAdd][addCount] = u_acc[((4*(i+1))-1)-j];
			addCount++;
		}
	}

	uint8_t *u_gyro = reinterpret_cast<uint8_t *>(gyro);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_rawAccGyro[toAdd][addCount] = u_gyro[((4 * (i + 1)) - 1) - j];
			addCount++;
		}
	}
}

void ComsEncoder::sendPitchRoll(float pitch, float roll)
{

	if (_pitchRoll_man.isFull())
	{
		//@TODO notify of overflow
		return;
	}

	int toAdd = _pitchRoll_man.add();

	_pitchRoll[toAdd][0] = C_COMS_CODE_PITCH_ROLL;

	uint8_t *u_pitch = reinterpret_cast<uint8_t *>(&pitch);
	int addCount = 1;

		for (int j = 0; j < 4; j++)
		{
			_pitchRoll[toAdd][addCount] = u_pitch[j];
			addCount++;
		}
	
	uint8_t *u_roll = reinterpret_cast<uint8_t *>(&roll);

		for (int j = 0; j < 4; j++)
		{
			_pitchRoll[toAdd][addCount] = u_roll[j];
			addCount++;
		}
	}


void ComsEncoder::sendLidarPoint(float angle, float distance)
{

	if (_lidarData_man.isFull())
	{
		//@TODO notify of overflow
		return;
	}

	int toAdd = _lidarData_man.add();

	_lidarData[toAdd][0] = C_COMS_CODE_LIDAR_POINT;

	uint8_t *u_lidarAngle = reinterpret_cast<uint8_t *>(&angle);
	int addCount = 1;

	for (int j = 0; j < 4; j++)
	{
		_lidarData[toAdd][addCount] = u_lidarAngle [j];
		addCount++;
	}

	uint8_t *u_lidarDistance = reinterpret_cast<uint8_t *>(&distance);

	for (int j = 0; j < 4; j++)
	{
		_lidarData[toAdd][addCount] = u_lidarDistance[j];
		addCount++;
	}
}

void ComsEncoder::sendLidarEOSweep(float pitch, float roll, float yaw)
{

	if (_lidarData_man.isFull())
	{
		//@TODO add size check
		//@TODO notify of overflow

		return;
	}

	int toAdd = _lidarData_man.add();

	_lidarData[toAdd][0] = C_COMS_CODE_LIDAR_EOS1;

	uint8_t *u_lidarPitch = reinterpret_cast<uint8_t *>(&pitch);
	int addCount = 1;

	for (int j = 0; j < 4; j++)
	{
		_lidarData[toAdd][addCount] = u_lidarPitch[j];
		addCount++;
	}

	uint8_t *u_lidarRoll = reinterpret_cast<uint8_t *>(&roll);

	for (int j = 0; j < 4; j++)
	{
		_lidarData[toAdd][addCount] = u_lidarRoll[j];
		addCount++;
	}

	toAdd = _lidarData_man.add();
	_lidarData[toAdd][0] = C_COMS_CODE_LIDAR_EOS2;

	uint8_t *u_lidarYaw = reinterpret_cast<uint8_t *>(&yaw);
	addCount = 1;

	for (int j = 0; j < 4; j++)
	{
		_lidarData[toAdd][addCount] = u_lidarYaw[j];
		addCount++;
	}

}