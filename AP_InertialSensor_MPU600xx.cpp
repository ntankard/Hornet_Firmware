#include "AP_InertialSensor_MPU600xx.h"
#include "Arduino.h"


#define MPU6050_I2C_ADDRESS 0x68
// MPU 6000 registers
#define MPUREG_WHOAMI 0x75 //
#define MPUREG_SMPLRT_DIV 0x19 //
#define MPUREG_CONFIG 0x1A //
#define MPUREG_GYRO_CONFIG 0x1B
#define MPUREG_ACCEL_CONFIG 0x1C
#define MPUREG_FIFO_EN 0x23
#define MPUREG_INT_PIN_CFG 0x37
#define MPUREG_INT_ENABLE 0x38
#define MPUREG_INT_STATUS 0x3A
#define MPUREG_ACCEL_XOUT_H 0x3B //
#define MPUREG_ACCEL_XOUT_L 0x3C //
#define MPUREG_ACCEL_YOUT_H 0x3D //
#define MPUREG_ACCEL_YOUT_L 0x3E //
#define MPUREG_ACCEL_ZOUT_H 0x3F //
#define MPUREG_ACCEL_ZOUT_L 0x40 //
#define MPUREG_TEMP_OUT_H 0x41//
#define MPUREG_TEMP_OUT_L 0x42//
#define MPUREG_GYRO_XOUT_H 0x43 //
#define MPUREG_GYRO_XOUT_L 0x44 //
#define MPUREG_GYRO_YOUT_H 0x45 //
#define MPUREG_GYRO_YOUT_L 0x46 //
#define MPUREG_GYRO_ZOUT_H 0x47 //
#define MPUREG_GYRO_ZOUT_L 0x48 //
#define MPUREG_USER_CTRL 0x6A //
#define MPUREG_PWR_MGMT_1 0x6B //
#define MPUREG_PWR_MGMT_2 0x6C //
#define MPUREG_FIFO_COUNTH 0x72
#define MPUREG_FIFO_COUNTL 0x73
#define MPUREG_FIFO_R_W 0x74


// Configuration bits MPU 3000 and MPU 6000 (not revised)?
#define BIT_SLEEP 0x40
#define BIT_H_RESET 0x80
#define BITS_CLKSEL 0x07
#define MPU_CLK_SEL_PLLGYROX 0x01
#define MPU_CLK_SEL_PLLGYROZ 0x03
#define MPU_EXT_SYNC_GYROX 0x02
#define BITS_FS_250DPS              0x00
#define BITS_FS_500DPS              0x08
#define BITS_FS_1000DPS             0x10
#define BITS_FS_2000DPS             0x18
#define BITS_FS_MASK                0x18
#define BITS_DLPF_CFG_256HZ_NOLPF2  0x00
#define BITS_DLPF_CFG_188HZ         0x01
#define BITS_DLPF_CFG_98HZ          0x02
#define BITS_DLPF_CFG_42HZ          0x03
#define BITS_DLPF_CFG_20HZ          0x04
#define BITS_DLPF_CFG_10HZ          0x05
#define BITS_DLPF_CFG_5HZ           0x06
#define BITS_DLPF_CFG_2100HZ_NOLPF  0x07
#define BITS_DLPF_CFG_MASK          0x07
#define BIT_INT_ANYRD_2CLEAR      0x10
#define BIT_RAW_RDY_EN        0x01
#define BIT_I2C_IF_DIS              0x10
#define BIT_INT_STATUS_DATA   0x01

// interupt stuff
//static int sReadNum;

AP_InertialSensor_MPU600xx *self;


AP_InertialSensor_MPU600xx::AP_InertialSensor_MPU600xx(SPIManager *theSPIManager, uint8_t cs_pin, uint8_t interruptPin)
{
	_sharedBusManager = theSPIManager;
	_address = cs_pin;
	_interruptPin = interruptPin;
	_isSPI = true;
	// MPU6000 chip select setup
	pinMode(cs_pin, OUTPUT);
	digitalWrite(cs_pin, HIGH);
	_readNum = 0;
}


AP_InertialSensor_MPU600xx::AP_InertialSensor_MPU600xx(I2CManager *theI2CManager, uint8_t interruptPin)
{
	_sharedBusManager = theI2CManager;
	_address = MPU6050_I2C_ADDRESS;
	_interruptPin = interruptPin;
	_isSPI = false;
	_readNum = 0;
}


bool AP_InertialSensor_MPU600xx::init()
{
	//@TODO adde deveice check here (may need error checking on read??)	

	// Chip reset
	register_write(MPUREG_PWR_MGMT_1, BIT_H_RESET);
	delay(100);
	// Wake up device and select GyroZ clock (better performance)
	register_write(MPUREG_PWR_MGMT_1, MPU_CLK_SEL_PLLGYROZ);
	delay(1);

	// Disable I2C bus (recommended on datasheet)
	if (_isSPI)
	{
		register_write(MPUREG_USER_CTRL, BIT_I2C_IF_DIS);
		delay(1);
	}

	// SAMPLE RATE
	register_write(MPUREG_SMPLRT_DIV, 0x04);     // Sample rate = 200Hz    Fsample= 1Khz/(4+1) = 200Hz
	delay(1);
	// FS & DLPF   FS=2000º/s, DLPF = 98Hz (low pass filter)
	register_write(MPUREG_CONFIG, BITS_DLPF_CFG_98HZ);
	delay(1);
	register_write(MPUREG_GYRO_CONFIG, BITS_FS_2000DPS);  // Gyro scale 2000º/s
	delay(1);
	register_write(MPUREG_ACCEL_CONFIG, 0x08);           // Accel scele 4g (4096LSB/g)
	delay(1);

	// INT CFG => Interrupt on Data Ready
	register_write(MPUREG_INT_ENABLE, BIT_RAW_RDY_EN);         // INT: Raw data ready
	delay(1);
	register_write(MPUREG_INT_PIN_CFG, BIT_INT_ANYRD_2CLEAR);  // INT: Clear on any read
	delay(1);
	// Oscillator set
	// register_write(MPUREG_PWR_MGMT_1,MPU_CLK_SEL_PLLGYROZ);
	delay(1);
	self = this;	//@TODO this is evil, fix this
	attachInterrupt(_interruptPin, data_interrupt, RISING);

	return true;
}

// MPU6000 new data interrupt on INT6
void AP_InertialSensor_MPU600xx::data_interrupt(void)
{
	self->getData();
}

void AP_InertialSensor_MPU600xx::register_write(uint8_t reg, uint8_t val)
{
	_sharedBusManager->write_reg(_address,reg, val);
}

uint8_t AP_InertialSensor_MPU600xx::register_read(uint8_t reg)
{
	return _sharedBusManager->read_reg(_address, reg);
}

void AP_InertialSensor_MPU600xx::getData()
{
	uint8_t addr = MPUREG_ACCEL_XOUT_H | 0x80;

	_sharedBusManager->read(_address, addr, _data, 14);	//@TODO magic number
	_readNum++;

	int32_t _sum[7];
	uint8_t byte_H, byte_L;


	int j = 0;
	for (int i = 0; i < 7; i++)
	{
		byte_H = _data[j];
		j++;
		byte_L = _data[j];
		j++;
		_sum[i] = (((int16_t)byte_H) << 8) | byte_L;
	}

	Serial.print(_sum[0]);
}
