#pragma once
#include "CONFIG.h"
#include "ComsDecoder.h"
#include "Runnable.h"

#ifdef USER_XBEE_COMS

//#include "Coms.h"
#include "XBee.h"

/**
* \brief	Com system implimented over a wirless XBee network
*/
class Coms : public Runnable
{
public:

	Coms();
	bool start();
	int run();
	bool canSend();
	void send(uint8_t *data, uint8_t dataLength);
	volatile MessageBuffer_Passer* getMessage()volatile { return _pendingMessage; }

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

	ComsDecoder _comsDecoder;

	volatile MessageBuffer_Passer* _pendingMessage;
};

#endif
