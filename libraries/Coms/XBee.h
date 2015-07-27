
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

/*#include "XBeeResponse.h"
#include "XBeeAddress64.h"



#include <inttypes.h>

#define SERIES_1
#define SERIES_2*/

#ifndef XBee_h
#define XBee_h

#include "XBeeResponse.h"
#include "XBeeRequest.h"
#include "XBee_Registers.h"
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif











// TODO add reset/clear method since responses are often reused
/**
 * Primary interface for communicating with an XBee Radio.
 * This class provides methods for sending and receiving packets with an XBee radio via the serial port.
 * The XBee radio must be configured in API (packet) mode (AP=2)
 * in order to use this software.
 * <p/>
 * Since this code is designed to run on a microcontroller, with only one thread, you are responsible for reading the
 * data off the serial buffer in a timely manner.  This involves a call to a variant of readPacket(...).
 * If your serial port is receiving data faster than you are reading, you can expect to lose packets.
 * Arduino only has a 128 byte serial buffer so it can easily overflow if two or more packets arrive
 * without a call to readPacket(...)
 * <p/>
 * In order to conserve resources, this class only supports storing one response packet in memory at a time.
 * This means that you must fully consume the packet prior to calling readPacket(...), because calling
 * readPacket(...) overwrites the previous response.
 * <p/>
 * This class creates an array of size MAX_FRAME_DATA_SIZE for storing the response packet.  You may want
 * to adjust this value to conserve memory.
 *
 * \author Andrew Rapp
 */
class XBee {
public:
	XBee();
	/**
	 * Reads all available serial bytes until a packet is parsed, an error occurs, or the buffer is empty.
	 * You may call <i>xbee</i>.getResponse().isAvailable() after calling this method to determine if
	 * a packet is ready, or <i>xbee</i>.getResponse().isError() to determine if
	 * a error occurred.
	 * <p/>
	 * This method should always return quickly since it does not wait for serial data to arrive.
	 * You will want to use this method if you are doing other timely stuff in your loop, where
	 * a delay would cause problems.
	 * NOTE: calling this method resets the current response, so make sure you first consume the
	 * current response
	 */
	void readPacket();
	/**
	 * Waits a maximum of <i>timeout</i> milliseconds for a response packet before timing out; returns true if packet is read.
	 * Returns false if timeout or error occurs.
	 */
	bool readPacket(int timeout);
	/**
	 * Reads until a packet is received or an error occurs.
	 * Caution: use this carefully since if you don't get a response, your Arduino code will hang on this
	 * call forever!! often it's better to use a timeout: readPacket(int)
	 */
	void readPacketUntilAvailable();
	/**
	 * Starts the serial connection on the specified serial port
	 */
	void begin(Stream &serial);
	void getResponse(XBeeResponse &response);
	/**
	 * Returns a reference to the current response
	 * Note: once readPacket is called again this response will be overwritten!
	 */
	XBeeResponse& getResponse();
	/**
	 * Sends a XBeeRequest (TX packet) out the serial port
	 */
	void send(XBeeRequest &request);
	//uint8_t sendAndWaitForResponse(XBeeRequest &request, int timeout);
	/**
	 * Returns a sequential frame id between 1 and 255
	 */
	uint8_t getNextFrameId();
	/**
	 * Specify the serial port.  Only relevant for Arduinos that support multiple serial ports (e.g. Mega)
	 */
	void setSerial(Stream &serial);
private:
	bool available();
	uint8_t read();
	void flush();
	void write(uint8_t val);
	void sendByte(uint8_t b, bool escape);
	void resetResponse();
	XBeeResponse _response;
	bool _escape;
	// current packet position for response.  just a state variable for packet parsing and has no relevance for the response otherwise
	uint8_t _pos;
	// last byte read
	uint8_t b;
	uint8_t _checksumTotal;
	uint8_t _nextFrameId;
	// buffer for incoming RX packets.  holds only the api specific frame data, starting after the api id byte and prior to checksum
	uint8_t _responseFrameData[MAX_FRAME_DATA_SIZE];
	Stream* _serial;
};

#endif //XBee_h
