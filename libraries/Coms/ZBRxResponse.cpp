#include "ZBRxResponse.h"

ZBRxResponse::ZBRxResponse() : RxDataResponse() {
	_remoteAddress64 = XBeeAddress64();
}

uint16_t ZBRxResponse::getRemoteAddress16() {
	return 	(getFrameData()[8] << 8) + getFrameData()[9];
}

uint8_t ZBRxResponse::getOption() {
	return getFrameData()[10];
}

// markers to read data from packet array.  this is the index, so the 12th item in the array
uint8_t ZBRxResponse::getDataOffset() {
	return 11;
}

uint8_t ZBRxResponse::getDataLength() {
	return getPacketLength() - getDataOffset() - 1;
}

XBeeAddress64& ZBRxResponse::getRemoteAddress64() {
	return _remoteAddress64;
}