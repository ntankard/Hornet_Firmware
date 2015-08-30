#include "ComsEncoder.h"

ComsEncoder::ComsEncoder(Coms* coms, Error *e) :_rawAccGyro_man(e), _messageBuffer_man(e), _pitchRoll_man(e), _lidarData_man(e)
{
	_e = e;
	_coms = coms;

	for (int i = 0; i < C_CL; i++)
	{
		_buffer[i] = new CircularBuffer<MessageBuffer_Passer*, C_COMENCODER_SIZE>(e);
	}
}

ComsEncoder::~ComsEncoder()
{
	for (int i = 0; i < C_CL; i++)
	{
		delete _buffer[i];
	}
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

		for (int i = 0; i < C_CL; i++)
		{
			if (!_buffer[i]->isEmpty())
			{
				MessageBuffer_Passer* toSend = _buffer[i]->remove();
				_coms->send(toSend->getPacket(), toSend->getPacketSize());
				toSend->unlock();

				//Serial.print((String)toSend->getPacket()[0] + " " + (String)toSend->getPacket()[1] + " " + (String)toSend->getPacket()[2] + " " + (String)toSend->getPacket()[3] + " ");
				//Serial.print('\n');

				//Serial.println("ID " + (String)toSend->getID());
				//Serial.println("SIZE " + (String)toSend->getPacketSize());

				return;
			}
		}

		//priority 2 (non critical nav data)
		/*if (!_rawAccGyro_man.isEmpty())
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
		}*/

	}
}

void ComsEncoder::sendData(MessageBuffer_Passer *data)
{
	if (_buffer[data->getComPri()]->isFull())
	{
		//@TODO add overflow detection
		return;
	}

	_buffer[data->getComPri()]->add(data);
	if (data->isLocked())
	{
		//@TODO throw
		return;
	}
	data->lock();
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
			_pitchRoll[toAdd][addCount] = u_pitch[4 - (j + 1)];
			addCount++;
		}
	
	uint8_t *u_roll = reinterpret_cast<uint8_t *>(&roll);

		for (int j = 0; j < 4; j++)
		{
			_pitchRoll[toAdd][addCount] = u_roll[4 - (j + 1)];
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
		_lidarData[toAdd][addCount] = u_lidarAngle [4-(j+1)];
		addCount++;
	}

	uint8_t *u_lidarDistance = reinterpret_cast<uint8_t *>(&distance);

	for (int j = 0; j < 4; j++)
	{
		_lidarData[toAdd][addCount] = u_lidarDistance[4 - (j + 1)];
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