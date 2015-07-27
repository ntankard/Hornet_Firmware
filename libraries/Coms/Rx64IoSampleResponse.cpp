#include "Rx64IoSampleResponse.h"
#include "XBee_Registers.h"

Rx64IoSampleResponse::Rx64IoSampleResponse() : RxIoSampleBaseResponse() {
	_remoteAddress = XBeeAddress64();
}

XBeeAddress64& Rx64IoSampleResponse::getRemoteAddress64() {
	return _remoteAddress;
}

uint8_t Rx64IoSampleResponse::getRssiOffset() {
	return 8;
}