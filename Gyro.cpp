#include "Gyro.h"

#ifdef USE_GYRO

Gyro::Gyro()
{
}

bool Gyro::start()
{
	// initialize device
	DEBUG_PRINTLN("Initializing I2C devices...");
	mpu.initialize();

	// verify connection
	DEBUG_PRINTLN("Testing device connections...");
	if (!mpu.testConnection())
	{
		DEBUG_PRINTLN("MPU6050 connection failed");
		return false;
	}
	DEBUG_PRINTLN("MPU6050 connection successful");

	// load and configure the DMP
	DEBUG_PRINTLN("Initializing DMP...");
	devStatus = mpu.dmpInitialize();

	// supply your own gyro offsets here, scaled for min sensitivity
	mpu.setXGyroOffset(220);
	mpu.setYGyroOffset(76);
	mpu.setZGyroOffset(-85);
	mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		DEBUG_PRINTLN("Enabling DMP...");
		mpu.setDMPEnabled(true);

		// enable Arduino interrupt detection
		//DEBUG_PRINTLN(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
		//attachInterrupt(0, dmpDataReady, RISING);
		//mpuIntStatus = mpu.getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		DEBUG_PRINTLN("DMP ready!");

		// get expected DMP packet size for later comparison
		packetSize = mpu.dmpGetFIFOPacketSize();
	}
	else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		DEBUG_PRINT("DMP Initialization failed (code ");
		DEBUG_PRINT(devStatus);
		DEBUG_PRINTLN(")");
		return false;
	}

	return true;
}

int Gyro::run()
{
	fifoCount = mpu.getFIFOCount();

	// is there a full packets worth of data?
	if (fifoCount < packetSize)
	{
		return 0;	//@TODO add timeout check
	}

	// check for overflow
	if (fifoCount >= 1024)
	{
		mpu.resetFIFO();	//@TODO may need to do more here
		DEBUG_PRINTLN("FIFO overflow!");
		return 0;
	}

	// empty all but 1 of the packets ( to prevent a cascading overflow)
	for (int i = 0; i < ((fifoCount / packetSize)-1); i++)
	{
		mpu.getFIFOBytes(fifoBuffer, packetSize);
	}

	// read a packet from FIFO
	mpu.getFIFOBytes(fifoBuffer, packetSize);

	// find Euler angles in degrees
	mpu.dmpGetQuaternion(&q, fifoBuffer);
	mpu.dmpGetGravity(&gravity, &q);
	mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);


	_toSend = _rollPitchYawSender.getAvailable();
	_toSend->getData()[0] = ypr[0]*10000;
	_toSend->getData()[1] = ypr[1]*10000;
	_toSend->getData()[2] = ypr[2]*10000;

	return 1;
}

volatile MessageBuffer_Passer* Gyro::getMessage()volatile
{
	return _toSend;
}

#endif