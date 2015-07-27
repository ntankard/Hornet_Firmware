#include "Rx64Response.h"
#include "XBee_Registers.h"

XBeeAddress64& Rx64Response::getRemoteAddress64() {
	return _remoteAddress;
}

Rx64Response::Rx64Response() : RxResponse() {
	_remoteAddress = XBeeAddress64();
}

uint8_t Rx64Response::getRssiOffset() {
	return RX_64_RSSI_OFFSET;
}
