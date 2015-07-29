#include "AccGyro.h"
#include "CONFIG.h"
#include "SPI.h"
#include "Arduino.h"
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
	float temperature;

	//delay(20);
	_ins.update();
	_ins.get_gyros(gyro);
	_ins.get_accels(accel);
	temperature = _ins.temperature();

	Serial.print("AX:");
	Serial.print(accel[0]);
	Serial.print("AY:");
	Serial.print(accel[1]);
	Serial.print("AZ:");
	Serial.print(accel[2]);

	Serial.print("GX:");
	Serial.print(gyro[0]);
	Serial.print("GY:");
	Serial.print(gyro[1]);
	Serial.print("GZ:");
	Serial.println(gyro[2]);;

	/*(if (_ins.read())
	{
		float accel[3];
		float gyro[3];

		_ins.get_gyros(gyro);
		_ins.get_accels(accel);

		Serial.print("AX:");
		Serial.print(accel[0]);
		Serial.print("AY:");
		Serial.print(accel[1]);
		Serial.print("AZ:");
		Serial.print(accel[2]);

		Serial.print("GX:");
		Serial.print(gyro[0]);
		Serial.print("GY:");
		Serial.print(gyro[1]);
		Serial.print("GZ:");
		Serial.println(gyro[2]);
	}*/
}



