#ifndef RxIoSampleBaseResponse_h
#define RxIoSampleBaseResponse_h

#include "RxResponse.h"
#include <inttypes.h>

/**
* Represents a Series 1 RX I/O Sample packet
*/
class RxIoSampleBaseResponse : public RxResponse {
public:
	RxIoSampleBaseResponse();
	/**
	* Returns the number of samples in this packet
	*/
	uint8_t getSampleSize();
	bool containsAnalog();
	bool containsDigital();
	/**
	* Returns true if the specified analog pin is enabled
	*/
	bool isAnalogEnabled(uint8_t pin);
	/**
	* Returns true if the specified digital pin is enabled
	*/
	bool isDigitalEnabled(uint8_t pin);
	/**
	* Returns the 10-bit analog reading of the specified pin.
	* Valid pins include ADC:0-5.  Sample index starts at 0
	*/
	uint16_t getAnalog(uint8_t pin, uint8_t sample);
	/**
	* Returns true if the specified pin is high/on.
	* Valid pins include DIO:0-8.  Sample index starts at 0
	*/
	bool isDigitalOn(uint8_t pin, uint8_t sample);
	uint8_t getSampleOffset();
private:
};

#endif