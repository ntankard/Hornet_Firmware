#include "AccGyro.h"
#include "CONFIG.h"
#include "SPI.h"
#include "Arduino.h"

#ifdef USE_ACC

AccGyro::AccGyro(HornetManager* theManager) :_ins(C_ACC_CS)
{
	_hornetManager = theManager;
}

#else

AccGyro::AccGyro(HornetManager* theManager)
{
	_hornetManager = theManager;
}

#endif

void AccGyro::start()
{
#ifdef USE_ACC
	//@TODO this needs to change if we share the SPI bus
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV16); // 1MHZ SPI rate
	// we need to stop the barometer from holding the SPI bus
	pinMode(40, OUTPUT);
	digitalWrite(40, HIGH);

	_ins.init();
#endif
}

void AccGyro::run()
{
#ifdef USE_ACC
	float accel[3];
	float gyro[3];

	if (_ins.update()){
		_ins.get_gyros(gyro);
		_ins.get_accels(accel);

		_hornetManager->newAccGyro(accel, gyro);
	}
#endif
}



