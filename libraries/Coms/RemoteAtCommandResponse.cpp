#include "RemoteAtCommandResponse.h"
#include "XBee_Registers.h"

RemoteAtCommandResponse::RemoteAtCommandResponse() : AtCommandResponse() {

}

uint8_t* RemoteAtCommandResponse::getCommand() {
	return getFrameData() + 11;
}

uint8_t RemoteAtCommandResponse::getStatus() {
	return getFrameData()[13];
}

bool RemoteAtCommandResponse::isOk() {
	// weird c++ behavior.  w/o this method, it calls AtCommandResponse::isOk(), which calls the AtCommandResponse::getStatus, not this.getStatus!!!
	return getStatus() == AT_OK;
}

uint8_t RemoteAtCommandResponse::getValueLength() {
	return getFrameDataLength() - 14;
}

uint8_t* RemoteAtCommandResponse::getValue() {
	if (getValueLength() > 0) {
		// value is only included for query commands.  set commands does not return a value
		return getFrameData() + 14;
	}

	return NULL;
}

uint16_t RemoteAtCommandResponse::getRemoteAddress16() {
	return uint16_t((getFrameData()[9] << 8) + getFrameData()[10]);
}

XBeeAddress64& RemoteAtCommandResponse::getRemoteAddress64() {
	return _remoteAddress64;
}