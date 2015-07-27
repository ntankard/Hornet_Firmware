#include "FrameIdResponse.h"

FrameIdResponse::FrameIdResponse() {

}

uint8_t FrameIdResponse::getFrameId() {
	return getFrameData()[0];
}
