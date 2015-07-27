#ifndef RemoteAtCommandRequest_h
#define RemoteAtCommandRequest_h

#include "AtCommandRequest.h"
#include "XBeeAddress64.h"
#include <inttypes.h>

/**
* Represents an Remote AT Command TX packet
* The command is used to configure a remote XBee radio
*/
class RemoteAtCommandRequest : public AtCommandRequest {
public:
	RemoteAtCommandRequest();
	/**
	* Creates a RemoteAtCommandRequest with 16-bit address to set a command.
	* 64-bit address defaults to broadcast and applyChanges is true.
	*/
	RemoteAtCommandRequest(uint16_t remoteAddress16, uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength);
	/**
	* Creates a RemoteAtCommandRequest with 16-bit address to query a command.
	* 64-bit address defaults to broadcast and applyChanges is true.
	*/
	RemoteAtCommandRequest(uint16_t remoteAddress16, uint8_t *command);
	/**
	* Creates a RemoteAtCommandRequest with 64-bit address to set a command.
	* 16-bit address defaults to broadcast and applyChanges is true.
	*/
	RemoteAtCommandRequest(XBeeAddress64 &remoteAddress64, uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength);
	/**
	* Creates a RemoteAtCommandRequest with 16-bit address to query a command.
	* 16-bit address defaults to broadcast and applyChanges is true.
	*/
	RemoteAtCommandRequest(XBeeAddress64 &remoteAddress64, uint8_t *command);
	uint16_t getRemoteAddress16();
	void setRemoteAddress16(uint16_t remoteAddress16);
	XBeeAddress64& getRemoteAddress64();
	void setRemoteAddress64(XBeeAddress64 &remoteAddress64);
	bool getApplyChanges();
	void setApplyChanges(bool applyChanges);
	uint8_t getFrameData(uint8_t pos);
	uint8_t getFrameDataLength();
	static XBeeAddress64 broadcastAddress64;
	//	static uint16_t broadcast16Address;
private:
	XBeeAddress64 _remoteAddress64;
	uint16_t _remoteAddress16;
	bool _applyChanges;
};


#endif