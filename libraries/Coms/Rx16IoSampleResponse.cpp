#include "Rx16IoSampleResponse.h"

Rx16IoSampleResponse::Rx16IoSampleResponse() : RxIoSampleBaseResponse() {

}

uint16_t Rx16IoSampleResponse::getRemoteAddress16() {
	return (uint16_t)((getFrameData()[0] << 8) + getFrameData()[1]);
}

uint8_t Rx16IoSampleResponse::getRssiOffset() {
	return 2;
}
