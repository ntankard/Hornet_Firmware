#include "Tx64Request.h"
#include "XBee_Registers.h"

Tx64Request::Tx64Request() : PayloadRequest(TX_64_REQUEST, DEFAULT_FRAME_ID, NULL, 0) {

}

Tx64Request::Tx64Request(XBeeAddress64 &addr64, uint8_t option, uint8_t *data, uint8_t dataLength, uint8_t frameId) : PayloadRequest(TX_64_REQUEST, frameId, data, dataLength) {
	_addr64 = addr64;
	_option = option;
}

Tx64Request::Tx64Request(XBeeAddress64 &addr64, uint8_t *data, uint8_t dataLength) : PayloadRequest(TX_64_REQUEST, DEFAULT_FRAME_ID, data, dataLength) {
	_addr64 = addr64;
	_option = ACK_OPTION;
}

uint8_t Tx64Request::getFrameData(uint8_t pos) {

	if (pos == 0) {
		return (_addr64.getMsb() >> 24) & 0xff;
	}
	else if (pos == 1) {
		return (_addr64.getMsb() >> 16) & 0xff;
	}
	else if (pos == 2) {
		return (_addr64.getMsb() >> 8) & 0xff;
	}
	else if (pos == 3) {
		return _addr64.getMsb() & 0xff;
	}
	else if (pos == 4) {
		return (_addr64.getLsb() >> 24) & 0xff;
	}
	else if (pos == 5) {
		return (_addr64.getLsb() >> 16) & 0xff;
	}
	else if (pos == 6) {
		return(_addr64.getLsb() >> 8) & 0xff;
	}
	else if (pos == 7) {
		return _addr64.getLsb() & 0xff;
	}
	else if (pos == 8) {
		return _option;
	}
	else {
		return getPayload()[pos - TX_64_API_LENGTH];
	}
}

uint8_t Tx64Request::getFrameDataLength() {
	return TX_64_API_LENGTH + getPayloadLength();
}

XBeeAddress64& Tx64Request::getAddress64() {
	return _addr64;
}

void Tx64Request::setAddress64(XBeeAddress64& addr64) {
	_addr64 = addr64;
}

uint8_t Tx64Request::getOption() {
	return _option;
}

void Tx64Request::setOption(uint8_t option) {
	_option = option;
}