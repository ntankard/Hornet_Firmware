#pragma once
#include "CONFIG.h"
#include "Runnable.h"

#ifdef USE_GYRO

#include "MPU6050.h"
#include "MessageBuffer.h"

class Gyro : public Runnable
{
public:

	Gyro();
	bool start();
	int getNORegisters();
	volatile MessageBuffer_Passer* getRegister();
	void addRegister(volatile MessageBuffer_Passer* newRegister){}
	bool run();

private:

	MPU6050 mpu;

	// MPU control/status vars
	bool dmpReady = false;  // set true if DMP init was successful
	uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
	uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
	uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
	uint16_t fifoCount;     // count of all bytes currently in FIFO
	uint8_t fifoBuffer[64]; // FIFO storage buffer

	// orientation/motion vars (reused to save time)
	Quaternion q;           // [w, x, y, z]         quaternion container
	VectorFloat gravity;    // [x, y, z]            gravity vector
	float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

	volatile MessageBuffer<MB_ROLL_PITCH_YAW, 3> _rollPitchYaw_Register;

	//volatile MessageBuffer_Manager<MB_ROLL_PITCH_YAW_SETTINGS> _rollPitchYawSender;
	//volatile MessageBuffer_Passer* _toSend;
};

#else
#include "Arduino.h"

class Gyro : public Runnable
{
public:
	Gyro(){}
	bool start(){return true;}
	int run(){return 0;}
	volatile MessageBuffer_Passer* getMessage()volatile{return NULL;}
private:

};
#endif