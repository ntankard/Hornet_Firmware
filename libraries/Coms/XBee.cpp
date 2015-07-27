/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "XBee.h"

/*#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "HardwareSerial.h"*/


String toHex(uint8_t b)
{
	String hex[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };
	uint8_t hi;
	uint8_t lo;
	hi = (b >> 4);
	lo = (b & 0b00001111);
	return hex[hi] + hex[lo];
}



void XBee::resetResponse() {
	_pos = 0;
	_escape = false;
	_checksumTotal = 0;
	_response.reset();
}

XBee::XBee(): _response(XBeeResponse()) {
        _pos = 0;
        _escape = false;
        _checksumTotal = 0;
        _nextFrameId = 0;

        _response.init();
        _response.setFrameData(_responseFrameData);
		// Contributed by Paul Stoffregen for Teensy support
#if defined(__AVR_ATmega32U4__) || defined(__MK20DX128__)
        _serial = &Serial1;
#else
        _serial = &Serial;
#endif
}

uint8_t XBee::getNextFrameId() {

	_nextFrameId++;

	if (_nextFrameId == 0) {
		// can't send 0 because that disables status response
		_nextFrameId = 1;
	}

	return _nextFrameId;
}

// Support for SoftwareSerial. Contributed by Paul Stoffregen
void XBee::begin(Stream &serial) {
	_serial = &serial;
}

void XBee::setSerial(Stream &serial) {
	_serial = &serial;
}

bool XBee::available() {
	return _serial->available();
}

uint8_t XBee::read() {
	return _serial->read();
} 

void XBee::flush() {
	_serial->flush();
} 

void XBee::write(uint8_t val) {
	_serial->write(val);
}

XBeeResponse& XBee::getResponse() {
	return _response;
}

// TODO how to convert response to proper subclass?
void XBee::getResponse(XBeeResponse &response) {

	response.setMsbLength(_response.getMsbLength());
	response.setLsbLength(_response.getLsbLength());
	response.setApiId(_response.getApiId());
	response.setFrameLength(_response.getFrameDataLength());

	response.setFrameData(_response.getFrameData());
}

void XBee::readPacketUntilAvailable() {
	while (!(getResponse().isAvailable() || getResponse().isError())) {
		// read some more
		readPacket();
	}
}

bool XBee::readPacket(int timeout) {

	if (timeout < 0) {
		return false;
	}

	unsigned long start = millis();

    while (int((millis() - start)) < timeout) {

     	readPacket();

     	if (getResponse().isAvailable()) {
     		return true;
     	} else if (getResponse().isError()) {
     		return false;
     	}
    }

    // timed out
    return false;
}

void XBee::readPacket() {
	// reset previous response
	if (_response.isAvailable() || _response.isError()) {
		// discard previous packet and start over
		resetResponse();
	}

    while (available()) {

        b = read();
		

        if (_pos > 0 && b == START_BYTE && ATAP == 2) {
        	// new packet start before previous packeted completed -- discard previous packet and start over
        	_response.setErrorCode(UNEXPECTED_START_BYTE);
        	return;
        }

		if (_pos > 0 && b == ESCAPE) {
			if (available()) {
				b = read();
				b = 0x20 ^ b;
			} else {
				// escape byte.  next byte will be
				_escape = true;
				continue;
			}
		}

		if (_escape == true) {
			b = 0x20 ^ b;
			_escape = false;
		}

		// checksum includes all bytes starting with api id
		if (_pos >= API_ID_INDEX) {
			_checksumTotal+= b;
		}

        switch(_pos) {
			case 0:
		        if (b == START_BYTE) {
		        	_pos++;
		        }

		        break;
			case 1:
				// length msb
				_response.setMsbLength(b);
				_pos++;

				break;
			case 2:
				// length lsb
				_response.setLsbLength(b);
				_pos++;

				break;
			case 3:
				_response.setApiId(b);
				_pos++;

				break;
			default:
				// starts at fifth byte

				if (_pos > MAX_FRAME_DATA_SIZE) {
					// exceed max size.  should never occur
					_response.setErrorCode(PACKET_EXCEEDS_BYTE_ARRAY_LENGTH);
					return;
				}

				// check if we're at the end of the packet
				// packet length does not include start, length, or checksum bytes, so add 3
				if (_pos == (_response.getPacketLength() + 3)) {
					// verify checksum

					//std::cout << "read checksum " << static_cast<unsigned int>(b) << " at pos " << static_cast<unsigned int>(_pos) << std::endl;

					if ((_checksumTotal & 0xff) == 0xff) {
						_response.setChecksum(b);
						_response.setAvailable(true);

						_response.setErrorCode(NO_ERROR);
					} else {
						// checksum failed
						_response.setErrorCode(CHECKSUM_FAILURE);
					}

					// minus 4 because we start after start,msb,lsb,api and up to but not including checksum
					// e.g. if frame was one byte, _pos=4 would be the byte, pos=5 is the checksum, where end stop reading
					_response.setFrameLength(_pos - 4);

					// reset state vars
					_pos = 0;

					return;
				} else {
					// add to packet array, starting with the fourth byte of the apiFrame
					Serial.println(toHex(b));
					Serial.println(_pos - 4);
					_response.getFrameData()[_pos - 4] = b;
					_pos++;
				}
        }
    }
}

// it's peanut butter jelly time!!










// contributed by user repat123 on issue tracker
//bool XBeeAddress64::operator==(XBeeAddress64 addr) {
//    return ((_lsb == addr.getLsb()) && (_msb == addr.getMsb()));
//}

//bool XBeeAddress64::operator!=(XBeeAddress64 addr) {
//            return !(*this == addr);
//}








// TODO
//GenericRequest::GenericRequest(uint8_t* frame, uint8_t len, uint8_t apiId): XBeeRequest(apiId, *(frame), len) {
//	_frame = frame;
//}

void XBee::send(XBeeRequest &request) {
	// the new new deal

	sendByte(START_BYTE, false);

	// send length
	uint8_t msbLen = ((request.getFrameDataLength() + 2) >> 8) & 0xff;
	uint8_t lsbLen = (request.getFrameDataLength() + 2) & 0xff;

	sendByte(msbLen, true);
	sendByte(lsbLen, true);

	// api id
	sendByte(request.getApiId(), true);
	sendByte(request.getFrameId(), true);

	uint8_t checksum = 0;

	// compute checksum, start at api id
	checksum+= request.getApiId();
	checksum+= request.getFrameId();

	//std::cout << "frame length is " << static_cast<unsigned int>(request.getFrameDataLength()) << std::endl;

	for (int i = 0; i < request.getFrameDataLength(); i++) {
//		std::cout << "sending byte [" << static_cast<unsigned int>(i) << "] " << std::endl;
		sendByte(request.getFrameData(i), true);
		checksum+= request.getFrameData(i);
	}

	// perform 2s complement
	checksum = 0xff - checksum;

//	std::cout << "checksum is " << static_cast<unsigned int>(checksum) << std::endl;

	// send checksum
	sendByte(checksum, true);

	// send packet (Note: prior to Arduino 1.0 this flushed the incoming buffer, which of course was not so great)
	flush();
}

void XBee::sendByte(uint8_t b, bool escape) {

	if (escape && (b == START_BYTE || b == ESCAPE || b == XON || b == XOFF)) {
//		std::cout << "escaping byte [" << toHexString(b) << "] " << std::endl;
		write(ESCAPE);
		write(b ^ 0x20);
	} else {
		write(b);
	}
}

