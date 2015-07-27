#include "AtCommandResponse.h"
#include "XBee_Registers.h"




AtCommandResponse::AtCommandResponse() {

}

uint8_t* AtCommandResponse::getCommand() {
	return getFrameData() + 1;
}

uint8_t AtCommandResponse::getStatus() {
	return getFrameData()[3];
}

uint8_t AtCommandResponse::getValueLength() {
	return getFrameDataLength() - 4;
}

uint8_t* AtCommandResponse::getValue() {
	if (getValueLength() > 0) {
		// value is only included for query commands.  set commands does not return a value
		return getFrameData() + 4;
	}

	return NULL;
}

bool AtCommandResponse::isOk() {
	return getStatus() == AT_OK;
}