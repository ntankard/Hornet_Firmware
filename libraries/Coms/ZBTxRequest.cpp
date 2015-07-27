#include "ZBTxRequest.h"
#include "XBee_Registers.h"

ZBTxRequest::ZBTxRequest() : PayloadRequest(ZB_TX_REQUEST, DEFAULT_FRAME_ID, NULL, 0) {

}

ZBTxRequest::ZBTxRequest(XBeeAddress64 &addr64, uint16_t addr16, uint8_t broadcastRadius, uint8_t option, uint8_t *data, uint8_t dataLength, uint8_t frameId) : PayloadRequest(ZB_TX_REQUEST, frameId, data, dataLength) {
	_addr64 = addr64;
	_addr16 = addr16;
	_broadcastRadius = broadcastRadius;
	_option = option;
}

ZBTxRequest::ZBTxRequest(XBeeAddress64 &addr64, uint8_t *data, uint8_t dataLength) : PayloadRequest(ZB_TX_REQUEST, DEFAULT_FRAME_ID, data, dataLength) {
	_addr64 = addr64;
	_addr16 = ZB_BROADCAST_ADDRESS;
	_broadcastRadius = ZB_BROADCAST_RADIUS_MAX_HOPS;
	_option = ZB_TX_UNICAST;
}

uint8_t ZBTxRequest::getFrameData(uint8_t pos) {
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
		return  (_addr64.getLsb() >> 16) & 0xff;
	}
	else if (pos == 6) {
		return (_addr64.getLsb() >> 8) & 0xff;
	}
	else if (pos == 7) {
		return _addr64.getLsb() & 0xff;
	}
	else if (pos == 8) {
		return (_addr16 >> 8) & 0xff;
	}
	else if (pos == 9) {
		return _addr16 & 0xff;
	}
	else if (pos == 10) {
		return _broadcastRadius;
	}
	else if (pos == 11) {
		return _option;
	}
	else {
		return getPayload()[pos - ZB_TX_API_LENGTH];
	}
}

uint8_t ZBTxRequest::getFrameDataLength() {
	return ZB_TX_API_LENGTH + getPayloadLength();
}

XBeeAddress64& ZBTxRequest::getAddress64() {
	return _addr64;
}

uint16_t ZBTxRequest::getAddress16() {
	return _addr16;
}

uint8_t ZBTxRequest::getBroadcastRadius() {
	return _broadcastRadius;
}

uint8_t ZBTxRequest::getOption() {
	return _option;
}

void ZBTxRequest::setAddress64(XBeeAddress64& addr64) {
	_addr64 = addr64;
}

void ZBTxRequest::setAddress16(uint16_t addr16) {
	_addr16 = addr16;
}

void ZBTxRequest::setBroadcastRadius(uint8_t broadcastRadius) {
	_broadcastRadius = broadcastRadius;
}

void ZBTxRequest::setOption(uint8_t option) {
	_option = option;
}