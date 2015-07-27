#include "RxResponse.h"

uint8_t RxResponse::getRssi() {
	return getFrameData()[getRssiOffset()];
}

uint8_t RxResponse::getOption() {
	return getFrameData()[getRssiOffset() + 1];
}

bool RxResponse::isAddressBroadcast() {
	return (getOption() & 2) == 2;
}

bool RxResponse::isPanBroadcast() {
	return (getOption() & 4) == 4;
}

uint8_t RxResponse::getDataLength() {
	return getPacketLength() - getDataOffset() - 1;
}

uint8_t RxResponse::getDataOffset() {
	return getRssiOffset() + 2;
}

RxResponse::RxResponse() : RxDataResponse() {

}