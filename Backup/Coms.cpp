#include "Coms.h"

Coms::Coms(ComsDecoder* comsDecoder)
{
	// setupt the object to notify on incoming messages
	_comsDecoder = comsDecoder;
}
