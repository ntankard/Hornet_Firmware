#include "RemoteAtCommandRequest.h"
#include "XBee_Registers.h"

XBeeAddress64 RemoteAtCommandRequest::broadcastAddress64 = XBeeAddress64(0x0, BROADCAST_ADDRESS);

RemoteAtCommandRequest::RemoteAtCommandRequest() : AtCommandRequest(NULL, NULL, 0) {
	_remoteAddress16 = 0;
	_applyChanges = false;
	setApiId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(uint16_t remoteAddress16, uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength) : AtCommandRequest(command, commandValue, commandValueLength) {
	_remoteAddress64 = broadcastAddress64;
	_remoteAddress16 = remoteAddress16;
	_applyChanges = true;
	setApiId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(uint16_t remoteAddress16, uint8_t *command) : AtCommandRequest(command, NULL, 0) {
	_remoteAddress64 = broadcastAddress64;
	_remoteAddress16 = remoteAddress16;
	_applyChanges = false;
	setApiId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(XBeeAddress64 &remoteAddress64, uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength) : AtCommandRequest(command, commandValue, commandValueLength) {
	_remoteAddress64 = remoteAddress64;
	// don't worry.. works for series 1 too!
	_remoteAddress16 = ZB_BROADCAST_ADDRESS;
	_applyChanges = true;
	setApiId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(XBeeAddress64 &remoteAddress64, uint8_t *command) : AtCommandRequest(command, NULL, 0) {
	_remoteAddress64 = remoteAddress64;
	_remoteAddress16 = ZB_BROADCAST_ADDRESS;
	_applyChanges = false;
	setApiId(REMOTE_AT_REQUEST);
}

uint16_t RemoteAtCommandRequest::getRemoteAddress16() {
	return _remoteAddress16;
}

void RemoteAtCommandRequest::setRemoteAddress16(uint16_t remoteAddress16) {
	_remoteAddress16 = remoteAddress16;
}

XBeeAddress64& RemoteAtCommandRequest::getRemoteAddress64() {
	return _remoteAddress64;
}

void RemoteAtCommandRequest::setRemoteAddress64(XBeeAddress64 &remoteAddress64) {
	_remoteAddress64 = remoteAddress64;
}

bool RemoteAtCommandRequest::getApplyChanges() {
	return _applyChanges;
}

void RemoteAtCommandRequest::setApplyChanges(bool applyChanges) {
	_applyChanges = applyChanges;
}


uint8_t RemoteAtCommandRequest::getFrameData(uint8_t pos) {
	if (pos == 0) {
		return (_remoteAddress64.getMsb() >> 24) & 0xff;
	}
	else if (pos == 1) {
		return (_remoteAddress64.getMsb() >> 16) & 0xff;
	}
	else if (pos == 2) {
		return (_remoteAddress64.getMsb() >> 8) & 0xff;
	}
	else if (pos == 3) {
		return _remoteAddress64.getMsb() & 0xff;
	}
	else if (pos == 4) {
		return (_remoteAddress64.getLsb() >> 24) & 0xff;
	}
	else if (pos == 5) {
		return (_remoteAddress64.getLsb() >> 16) & 0xff;
	}
	else if (pos == 6) {
		return(_remoteAddress64.getLsb() >> 8) & 0xff;
	}
	else if (pos == 7) {
		return _remoteAddress64.getLsb() & 0xff;
	}
	else if (pos == 8) {
		return (_remoteAddress16 >> 8) & 0xff;
	}
	else if (pos == 9) {
		return _remoteAddress16 & 0xff;
	}
	else if (pos == 10) {
		return _applyChanges ? 2 : 0;
	}
	else if (pos == 11) {
		return getCommand()[0];
	}
	else if (pos == 12) {
		return getCommand()[1];
	}
	else {
		return getCommandValue()[pos - REMOTE_AT_COMMAND_API_LENGTH];
	}
}

uint8_t RemoteAtCommandRequest::getFrameDataLength() {
	return REMOTE_AT_COMMAND_API_LENGTH + getCommandValueLength();
}