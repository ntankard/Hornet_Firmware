#pragma once
#include "CONFIG.h"

#if COM_MODE == COM_MODE_XBEE

#include "Coms.h"
#include "XBee.h"

/**
* \brief	Com system implimented over a wirless XBee network
*/
class XBee_Coms : public Coms
{
public:

	XBee_Coms(ComsDecoder* comsDecoder);
	bool start(){ return true; }
	void run();
	bool canSend();
	void send(uint8_t *data, uint8_t dataLength);

private:

	/** \brief	The XBee object */
	XBee _xbee;

	/** \brief	A reusable object to store the responce */
	Rx16Response _rx16;

	/** \brief	A reusable object to store the request */
	Tx16Request _tx16;

	/** \brief	A reusable object to store the status */
	TxStatusResponse _txStatus;

	/** \brief	How many times has a message been resent */
	int _resendCount;

	/** \brief	Is there a message waiting to be sent or confiurmed */
	bool _outstandingSent;
};

#endif
