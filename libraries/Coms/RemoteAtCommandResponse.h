#ifndef RemoteAtCommandResponse_h
#define RemoteAtCommandResponse_h

#include "AtCommandResponse.h"
#include "XBeeAddress64.h"
#include <inttypes.h>

/**
* Represents a Remote AT Command RX packet
*/
class RemoteAtCommandResponse : public AtCommandResponse {
public:
	RemoteAtCommandResponse();
	/**
	* Returns an array containing the two character command
	*/
	uint8_t* getCommand();
	/**
	* Returns the command status code.
	* Zero represents a successful command
	*/
	uint8_t getStatus();
	/**
	* Returns an array containing the command value.
	* This is only applicable to query commands.
	*/
	uint8_t* getValue();
	/**
	* Returns the length of the command value array.
	*/
	uint8_t getValueLength();
	/**
	* Returns the 16-bit address of the remote radio
	*/
	uint16_t getRemoteAddress16();
	/**
	* Returns the 64-bit address of the remote radio
	*/
	XBeeAddress64& getRemoteAddress64();
	/**
	* Returns true if command was successful
	*/
	bool isOk();
private:
	XBeeAddress64 _remoteAddress64;
};


#endif