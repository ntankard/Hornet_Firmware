#include "RxDataResponse.h"

RxDataResponse::RxDataResponse() : XBeeResponse() {

}

uint8_t RxDataResponse::getData(int index) {
	return getFrameData()[getDataOffset() + index];
}

uint8_t* RxDataResponse::getData() {
	return getFrameData() + getDataOffset();
}