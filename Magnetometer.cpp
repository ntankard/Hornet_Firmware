#include "Magnetometer.h"

#if ENABLE_MAG == ENABLED

Magnetometer::Magnetometer(SPIManager *theSPIManager) :_mag(theSPIManager, SSNOTpin_DEF, DRDYpin_DEF, RESETpin_DEF)
{
}

bool Magnetometer::start()
{
	_mag.init();
}
void Magnetometer::run()
{
	_mag.update();
}

#endif
