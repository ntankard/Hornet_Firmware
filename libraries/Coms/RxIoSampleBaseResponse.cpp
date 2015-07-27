#include "RxIoSampleBaseResponse.h"

RxIoSampleBaseResponse::RxIoSampleBaseResponse() : RxResponse() {

}

uint8_t RxIoSampleBaseResponse::getSampleOffset() {
	// sample starts 2 bytes after rssi
	return getRssiOffset() + 2;
}


uint8_t RxIoSampleBaseResponse::getSampleSize() {
	return getFrameData()[getSampleOffset()];
}

bool RxIoSampleBaseResponse::containsAnalog() {
	return (getFrameData()[getSampleOffset() + 1] & 0x7e) > 0;
}

bool RxIoSampleBaseResponse::containsDigital() {
	return (getFrameData()[getSampleOffset() + 1] & 0x1) > 0 || getFrameData()[getSampleOffset() + 2] > 0;
}

//uint16_t RxIoSampleBaseResponse::getAnalog0(uint8_t sample) {
//	return getAnalog(0, sample);
//}

bool RxIoSampleBaseResponse::isAnalogEnabled(uint8_t pin) {
	return (((getFrameData()[getSampleOffset() + 1] >> (pin + 1)) & 1) == 1);
}

bool RxIoSampleBaseResponse::isDigitalEnabled(uint8_t pin) {
	if (pin < 8) {
		return ((getFrameData()[getSampleOffset() + 4] >> pin) & 1) == 1;
	}
	else {
		return (getFrameData()[getSampleOffset() + 3] & 1) == 1;
	}
}

//	// verified (from XBee-API)
//	private int getSampleWidth() {
//		int width = 0;
//
//		// width of sample depends on how many I/O pins are enabled. add one for each analog that's enabled
//		for (int i = 0; i <= 5; i++) {
//			if (isAnalogEnabled(i)) {
//				// each analog is two bytes
//				width+=2;
//			}
//		}
//		
//		if (this.containsDigital()) {
//			// digital enabled takes two bytes, no matter how many pins enabled
//			width+= 2;
//		}
//		
//		return width;
//	}
//
//	private int getStartIndex() {
//
//		int startIndex;
//
//		if (this.getSourceAddress() instanceof XBeeAddress16) {
//			// 16 bit
//			startIndex = 7;
//		} else {
//			// 64 bit
//			startIndex = 13;
//		}
//		
//		return startIndex;
//	}
//	
//	public int getDigitalMsb(int sample) {
//		// msb digital always starts 3 bytes after sample size
//		return this.getProcessedPacketBytes()[this.getStartIndex() + 3 + this.getSampleWidth() * sample];
//	}
//	
//	public int getDigitalLsb(int sample) {
//		return this.getProcessedPacketBytes()[this.getStartIndex() + 3 + this.getSampleWidth() * sample + 1];
//	}	
//
//	public Boolean isDigitalOn(int pin, int sample) {
//		
//		if (sample < 0 || sample >= this.getSampleSize()) {
//			throw new IllegalArgumentException("invalid sample size: " + sample);
//		}
//		
//		if (!this.containsDigital()) {
//			throw new RuntimeException("Digital is not enabled");
//		}
//		
//		if (pin >= 0 && pin < 8) {
//			return ((this.getDigitalLsb(sample) >> pin) & 1) == 1;
//		} else if (pin == 8) {
//			// uses msb dio line
//			return (this.getDigitalMsb(sample) & 1) == 1;
//		} else {
//			throw new IllegalArgumentException("Invalid pin: " + pin);
//		}		
//	}
//	
//	public Integer getAnalog(int pin, int sample) {
//		
//		if (sample < 0 || sample >= this.getSampleSize()) {
//			throw new IllegalArgumentException("invalid sample size: " + sample);
//		}
//		
//		// analog starts 3 bytes after start of sample, if no dio enabled
//		int startIndex = this.getStartIndex() + 3;
//		
//		if (this.containsDigital()) {
//			// make room for digital i/o sample (2 bytes per sample)
//			startIndex+= 2;
//		}
//		
//		startIndex+= this.getSampleWidth() * sample;
//
//		// start depends on how many pins before this pin are enabled
//		// this will throw illegalargumentexception if invalid pin
//		for (int i = 0; i < pin; i++) {
//			if (isAnalogEnabled(i)) {
//				startIndex+=2;
//			}
//		}
//
//		return (this.getProcessedPacketBytes()[startIndex] << 8) + this.getProcessedPacketBytes()[startIndex + 1];		
//	}

// THIS IS WRONG
uint16_t RxIoSampleBaseResponse::getAnalog(uint8_t pin, uint8_t sample) {

	// analog starts 3 bytes after sample size, if no dio enabled
	uint8_t start = 3;

	if (containsDigital()) {
		// make room for digital i/o sample (2 bytes per sample)
		start += 2 * (sample + 1);
	}

	uint8_t spacing = 0;

	// spacing between samples depends on how many are enabled. add one for each analog that's enabled
	for (int i = 0; i <= 5; i++) {
		if (isAnalogEnabled(i)) {
			// each analog is two bytes
			spacing += 2;
		}
	}

	//	std::cout << "spacing is " << static_cast<unsigned int>(spacing) << std::endl;

	// start depends on how many pins before this pin are enabled
	for (int i = 0; i < pin; i++) {
		if (isAnalogEnabled(i)) {
			start += 2;
		}
	}

	start += sample * spacing;

	//	std::cout << "start for analog pin ["<< static_cast<unsigned int>(pin) << "]/sample " << static_cast<unsigned int>(sample) << " is " << static_cast<unsigned int>(start) << std::endl;

	//	std::cout << "returning index " << static_cast<unsigned int>(getSampleOffset() + start) << " and index " <<  static_cast<unsigned int>(getSampleOffset() + start + 1) << ", val is " << static_cast<unsigned int>(getFrameData()[getSampleOffset() + start] << 8) <<  " and " <<  + static_cast<unsigned int>(getFrameData()[getSampleOffset() + start + 1]) << std::endl;

	return (uint16_t)((getFrameData()[getSampleOffset() + start] << 8) + getFrameData()[getSampleOffset() + start + 1]);
}

bool RxIoSampleBaseResponse::isDigitalOn(uint8_t pin, uint8_t sample) {
	if (pin < 8) {
		return ((getFrameData()[getSampleOffset() + 4] >> pin) & 1) == 1;
	}
	else {
		return (getFrameData()[getSampleOffset() + 3] & 1) == 1;
	}
}


//bool RxIoSampleBaseResponse::isDigital0On(uint8_t sample) {
//	return isDigitalOn(0, sample);
//}