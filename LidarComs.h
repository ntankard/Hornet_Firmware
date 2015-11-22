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

/**
* \class	LidarComs
*
* \brief	Manages communications with a RPLIDAR
*/
class LidarComs
{
public:

	LidarComs(volatile Error* e);

	/**
	* \brief	Sends a request to the device
	*
	* \param	packet	The request to send
	*/
	void sendRequest(RequestType packet);

	/**
	* \brief	Process any incoming data
	*
	* \return	True if a full packet was received
	*/
	bool run();

	/**
	* \brief	Has atleast one data packet being received
	*
	* \return	True if a data pacekt has been received
	*/
	bool getIsDone(){ return (!(_dataCount == 0)); }

	/**
	* \brief	Get the last received info packet
	*
	* \return	The info packet
	*/
	InfoPacket getLastInfoPacket(){ return _lastInfoPacket; }

	/**
	* \brief	Get the last received health packet
	*
	* \return	The health packet
	*/
	HealthPacket getLastHealthPacket(){ return _lastHealthPacket; }

	/**
	* \brief	Get the last received data packet
	*
	* \return	The data packet
	*/
	DataPacket getLastDataPacket(){ _dataCount--; return _lastDataPacket; }

	/**
	* \brief	How many packets have been received?
	*
	* \return	The number of packets received
	*/
	int getDataCount(){ return _dataCount; }

	/**
	* \brief	Get the number of packets received
	*
	* \return	The number of packets received
	*/
	int getTotalCount(){ return _totalReceived; }

	/**
	* \brief	Get the number of missed packets
	*
	* \return	The number of missed packets
	*/
	int getMissed(){ return _missed; }

	/**
	* \brief	Reset the send count
	*/
	void setTotalCount(int toSet){ _totalReceived = toSet; }

	/**
	* \brief	Reset the send count
	*/
	void setMissed(int toSet){ _missed = toSet; }

private:

	/**
	* \brief	Build part of a data packet
	*
	* \param	newByte	the byte to process

	* \return	true if the packet is complete
	*/
	bool processScan(uint8_t newByte);

	/**
	* \brief	Build part of an info packet
	*
	* \param	newByte	the byte to process

	* \return	true if the packet is complete
	*/
	bool processInfo(uint8_t newByte);

	/**
	* \brief	Build part of a health packet
	*
	* \param	newByte	the byte to process
	*
	* \return	true if the packet is complete
	*/
	bool processHealth(uint8_t newByte);

	/**
	* \brief	Build part of a packet
	*
	* \return	true if the packet is complete
	*/
	bool processIncomingData();

	/** \brief	The shared error object */
	volatile Error* _e;

	/** \brief	 The current outstanding request */
	RequestType _requestType;

	/** \brief	Has the descriptor been received yet? */
	bool _descriptorReceived;

	/** \brief	The number of packets received */
	int _readCount;

	/** \brief	The last info packet */
	InfoPacket _lastInfoPacket;

	/** \brief	The last health packet */
	HealthPacket _lastHealthPacket;

	/** \brief	The last data packet */
	DataPacket _lastDataPacket;

	/** \brief	The pending data packet */
	DataPacket _buildDataPacket;

	/** \brief	The number of bytes read */
	int _dataCount;

	/** \brief	The number of packets received (for loss tracking) */
	int _totalReceived;

	/** \brief	The number of packets missed (for loss tracking) */
	int _missed;
	int _maxBuffer;
};

#endif