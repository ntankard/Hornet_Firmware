#include "LidarComs.h"

#ifdef USE_LIDAR

// packets headers
#define RPLIDAR_CMD_SYNC_BYTE 0xA5
#define RPLIDAR_ANS_SYNC_BYTE1 0xA5
#define RPLIDAR_ANS_SYNC_BYTE2 0x5A

// packets commands
#define RPLIDAR_CMD_GET_DEVICE_INFO 0x50
#define RPLIDAR_CMD_GET_DEVICE_HEALTH 0x52
#define RPLIDAR_CMD_SCAN 0x20
#define RPLIDAR_CMD_FORCE_SCAN 0x21
#define RPLIDAR_CMD_RESET 0x40

// outbound packets
byte RPLIDAR_CMDS[] = { RPLIDAR_CMD_SCAN,
						RPLIDAR_CMD_FORCE_SCAN,
						RPLIDAR_CMD_GET_DEVICE_INFO,
						RPLIDAR_CMD_GET_DEVICE_HEALTH,
						RPLIDAR_CMD_RESET
};

// packet responces (see above)
const uint8_t DESCRIPTOR_RESPONSE[4][7] = { { RPLIDAR_ANS_SYNC_BYTE1, RPLIDAR_ANS_SYNC_BYTE2, 0x05, 0x00, 0x00, 0x40, 0x81 },
											{ RPLIDAR_ANS_SYNC_BYTE1, RPLIDAR_ANS_SYNC_BYTE2, 0x05, 0x00, 0x00, 0x40, 0x81 },
											{ RPLIDAR_ANS_SYNC_BYTE1, RPLIDAR_ANS_SYNC_BYTE2, 0x14, 0x00, 0x00, 0x00, 0x04 },
											{ RPLIDAR_ANS_SYNC_BYTE1, RPLIDAR_ANS_SYNC_BYTE2, 0x03, 0x00, 0x00, 0x00, 0x06 }
}; 


//-----------------------------------------------------------------------------------------------------------------------------

LidarComs::LidarComs(volatile Error* e)
{
	_e = e;
	_requestType = None;
	_descriptorReceived = false;
	_dataCount = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void LidarComs::sendRequest(RequestType packet)
{
	// sanity check
	if (packet < 0 || packet > 4)
	{
		_e->add(E_INDEX_OUT_BOUNDS, __LINE__);
	}

	// clear all inbound messages to prevent furure errors
	while (C_LIDAR_SERIAL.available())
	{
		char c = C_LIDAR_SERIAL.read();
	}

	// send the pacekt
	C_LIDAR_SERIAL.flush();
	C_LIDAR_SERIAL.write(RPLIDAR_CMD_SYNC_BYTE);
	C_LIDAR_SERIAL.write(RPLIDAR_CMDS[packet]);
	_requestType = packet;

	// resent pacekt responce
	_dataCount = 0;
	_descriptorReceived = false;
	_readCount = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool LidarComs::run()
{
	// check for buffer overflow
	int bufferSize = C_LIDAR_SERIAL.available();
	if (bufferSize >= 250)
	{
		_e->add(E_BUFFER_OVERFLOW, __LINE__);
		return false;
	}

	// process pats of packets
	for (int i = 0; i < bufferSize; i++)
	{
		uint8_t currentByte = C_LIDAR_SERIAL.read();
		if (_descriptorReceived)
		{
			switch (_requestType)
			{
			case None:
				break;
			case Scan:
				_buildDataPacket.raw.rawData[_readCount] = currentByte;
				_readCount++;
				if (_readCount >= 5)
				{
					_readCount = 0;
					_dataCount++;
					for (int i = 0; i < 5; i++)
					{
						_lastDataPacket.raw.rawData[i] = _buildDataPacket.raw.rawData[i];
					}

					// dump and extra packets
					int loop = bufferSize - i - 1;
					for (int i = 0; i < (((loop / 5)) * 5); i++)
					{
						C_LIDAR_SERIAL.read();
					}

					return true;
				}
				break;
			case Force_Scan:
				_buildDataPacket.raw.rawData[_readCount] = currentByte;
				_readCount++;
				if (_readCount >= 5)
				{
					_dataCount++;
					_readCount = 0;
					for (int i = 0; i < 5; i++)
					{
						_lastDataPacket.raw.rawData[i] = _buildDataPacket.raw.rawData[i];
					}

					// dump and extra packets
					int loop = bufferSize - i - 1;
					for (int i = 0; i < (((loop / 5)) * 5); i++)
					{
						C_LIDAR_SERIAL.read();
					}

					return true;
				}
				break;
			case Get_Info:
				_lastInfoPacket.rawData[_readCount] = currentByte;
				_readCount++;
				if (_readCount >= 20)
				{
					_readCount = 0;
					_dataCount = 1;
					return true;
				}
				break;
			case Get_Health:
				_lastHealthPacket.raw.rawData[_readCount] = currentByte;
				_readCount++;
				if (_readCount >= 3)
				{
					_readCount = 0;
					_dataCount = 1;
					return true;
				}
				break;
			default:
				_e->add(E_PACKET_CORRUPTION, __LINE__);
				break;
			}
		}
		else
		{
			if (currentByte == DESCRIPTOR_RESPONSE[_requestType][_readCount])
			{
				_readCount++;
				if (_readCount >= 7)
				{
					_descriptorReceived = true;
					_readCount = 0;
					return true;
				}
			}
			else
			{
				//TP((String)_requestType);
				//_e->add(E_PACKET_CORRUPTION, __LINE__);
				return false;
			}
		}
	}
	return true;
}
#endif