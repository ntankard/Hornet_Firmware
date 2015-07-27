#include "AtCommandRequest.h"
#include "XBee_Registers.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

AtCommandRequest::AtCommandRequest() : XBeeRequest(AT_COMMAND_REQUEST, DEFAULT_FRAME_ID) {
	_command = NULL;
	clearCommandValue();
}

AtCommandRequest::AtCommandRequest(uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength) : XBeeRequest(AT_COMMAND_REQUEST, DEFAULT_FRAME_ID) {
	_command = command;
	_commandValue = commandValue;
	_commandValueLength = commandValueLength;
}

AtCommandRequest::AtCommandRequest(uint8_t *command) : XBeeRequest(AT_COMMAND_REQUEST, DEFAULT_FRAME_ID) {
	_command = command;
	clearCommandValue();
}

uint8_t* AtCommandRequest::getCommand() {
	return _command;
}

uint8_t* AtCommandRequest::getCommandValue() {
	return _commandValue;
}

uint8_t AtCommandRequest::getCommandValueLength() {
	return _commandValueLength;
}

void AtCommandRequest::setCommand(uint8_t* command) {
	_command = command;
}

void AtCommandRequest::setCommandValue(uint8_t* value) {
	_commandValue = value;
}

void AtCommandRequest::setCommandValueLength(uint8_t length) {
	_commandValueLength = length;
}

uint8_t AtCommandRequest::getFrameData(uint8_t pos) {

	if (pos == 0) {
		return _command[0];
	}
	else if (pos == 1) {
		return _command[1];
	}
	else {
		return _commandValue[pos - AT_COMMAND_API_LENGTH];
	}
}

void AtCommandRequest::clearCommandValue() {
	_commandValue = NULL;
	_commandValueLength = 0;
}

//void AtCommandRequest::reset() {
//	 XBeeRequest::reset();
//}

uint8_t AtCommandRequest::getFrameDataLength() {
	// command is 2 byte + length of value
	return AT_COMMAND_API_LENGTH + _commandValueLength;
}