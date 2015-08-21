#include "AccGyro.h"
#include "CONFIG.h"
#include "SPI.h"
#include "Arduino.h"

#ifdef USE_ACC

AccGyro::AccGyro(HornetManager* theManager, Error* e) :_ins(C_ACC_CS), _pitchBuffer(e), _rollBuffer(e)
{
	_hornetManager = theManager;
	_e = e;
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

		// Calculate pitch and roll
		double g = sqrt(pow(accel[0], 2) + pow(accel[1], 2) + pow(accel[2], 2));
		float roll = (float)(asin(accel[0] / g));
		float pitch = (float)((asin(accel[1] / g)));

		_hornetManager->ND_RawAccGyro(accel, gyro);
		_hornetManager->ND_PitchRoll(_pitchBuffer.add(pitch), _rollBuffer.add(roll));
	}

}
#else
AccGyro::AccGyro(HornetManager* theManager, Error* e){}

void AccGyro::start(){}

void AccGyro::run(){}

#endif


