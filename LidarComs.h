#pragma once

#include "CONFIG.h"

#ifdef USE_LIDAR

#include "CircularBuffer.h"
#include "Error.h"
#include "CONFIG.h"



enum RequestType{ Scan = 0, Force_Scan = 1, Get_Info = 2, Get_Health = 3, Reset = 4,None =5 };

union InfoPacket
{
	uint8_t rawData[20];
	struct Payload
	{
		uint8_t model;
		uint16_t firmware_version;
		uint8_t hardware_version;
		uint8_t serialnum[16];
	}data;	
};


union HealthPacket
{
	struct Raw
	{
		uint8_t dump;
		uint8_t rawData[3];
	}raw;
	struct Payload
	{
		uint8_t dump;
		uint8_t status;
		uint16_t error_code;
	} data;
};

union DataPacket
{
	struct Raw
	{
		uint8_t dump;
		uint8_t rawData[5];
	}raw;

	struct Payload
	{
		uint8_t dump;
		uint8_t sync_quality;
		uint16_t angle;
		uint16_t distance;
	} data;
};


class LidarComs
{
public:
	LidarComs(volatile Error* e);
	void sendRequest(RequestType packet);
	bool run();
	bool getIsDone(){ return (!(_dataCount == 0)); }
	InfoPacket getLastInfoPacket(){ return _lastInfoPacket; }
	HealthPacket getLastHealthPacket(){ return _lastHealthPacket; }
	DataPacket getLastDataPacket(){ _dataCount--; return _lastDataPacket; }
	int getDataCount(){ return _dataCount; }

private:
	volatile Error* _e;
	RequestType _requestType;
	bool _descriptorReceived;
	int _readCount;
	InfoPacket _lastInfoPacket;
	HealthPacket _lastHealthPacket;
	DataPacket _lastDataPacket;
	DataPacket _buildDataPacket;
	int _dataCount;
	
	bool processIncomingData();

};

#endif