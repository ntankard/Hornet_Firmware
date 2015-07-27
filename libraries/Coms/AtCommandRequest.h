#ifndef AtCommandRequest_h
#define AtCommandRequest_h

#include "XBeeRequest.h"
#include <inttypes.h>

/**
* Represents an AT Command TX packet
* The command is used to configure the serially connected XBee radio
*/
class AtCommandRequest : public XBeeRequest {
public:
	AtCommandRequest();
	AtCommandRequest(uint8_t *command);
	AtCommandRequest(uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength);
	uint8_t getFrameData(uint8_t pos);
	uint8_t getFrameDataLength();
	uint8_t* getCommand();
	void setCommand(uint8_t* command);
	uint8_t* getCommandValue();
	void setCommandValue(uint8_t* command);
	uint8_t getCommandValueLength();
	void setCommandValueLength(uint8_t length);
	/**
	* Clears the optional commandValue and commandValueLength so that a query may be sent
	*/
	void clearCommandValue();
	//void reset();
private:
	uint8_t *_command;
	uint8_t *_commandValue;
	uint8_t _commandValueLength;
};

#endif