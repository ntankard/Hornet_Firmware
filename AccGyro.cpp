#include "AccGyro.h"
#include "CONFIG.h"
#include "SPI.h"
#include "Arduino.h"

#ifdef USE_ACC

AccGyro::AccGyro(HornetManager* theManager) :_ins(C_ACC_CS)
{
	_hornetManager = theManager;
}

void AccGyro::start()
{
	//@TODO this needs to change if we share the SPI bus
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV16); // 1MHZ SPI rate
	// we need to stop the barometer from holding the SPI bus
	pinMode(40, OUTPUT);
	digitalWrite(40, HIGH);

	_ins.init();

}

void AccGyro::run()
{
	float accel[3];
	float gyro[3];

	if (_ins.update()){
		_ins.get_gyros(gyro);
		_ins.get_accels(accel);

		_hornetManager->ND_AccGyro(accel, gyro);
	}

}
#else
AccGyro::AccGyro(HornetManager* theManager){}

void AccGyro::start(){}

void AccGyro::run(){}

#endif


