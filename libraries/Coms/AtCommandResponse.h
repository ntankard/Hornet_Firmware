#ifndef AtCommandResponse_h
#define AtCommandResponse_h

#include "FrameIdResponse.h"
#include <inttypes.h>

/**
* Represents an AT Command RX packet
*/
class AtCommandResponse : public FrameIdResponse {
public:
	AtCommandResponse();
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
	* Returns true if status equals AT_OK
	*/
	bool isOk();
};

#endif