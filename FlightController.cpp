#include "FlightController.h"

#include "CONFIG.h"
#include "Arduino.h"

#define MIN 1000
#define MAX 2000
#define MULTIPLYER 10

#if FLIGHT_MODE == EXTERNAL

//   TC2   0      TC6_IRQn   TC6_Handler   ID_TC6   D5(TIOA6)
#define CAPTURE_TC_R TC2
#define CAPTURE_CHANNEL_R 0
#define CAPTURE_IRQn_R TC6_IRQn
#define CAPTURE_Handler_R TC6_Handler
#define CAPTURE_ID_R ID_TC6
#define CAPTURE_PIN_R 5
#define CAPTURE_CLOCK_SELECTION_R TC_CMR_TCCLKS_TIMER_CLOCK3

//   TC2   1      TC7_IRQn   TC7_Handler   ID_TC7   D3(TIOA7)
#define CAPTURE_TC_P TC2
#define CAPTURE_CHANNEL_P 1
#define CAPTURE_IRQn_P TC7_IRQn
#define CAPTURE_Handler_P TC7_Handler
#define CAPTURE_ID_P ID_TC7
#define CAPTURE_PIN_P 3
#define CAPTURE_CLOCK_SELECTION_P TC_CMR_TCCLKS_TIMER_CLOCK3

//*   TC0   1      TC1_IRQn   TC1_Handler   ID_TC1   D61/A7 (TIOA1)
#define CAPTURE_TC_Y TC0
#define CAPTURE_CHANNEL_Y 1
#define CAPTURE_IRQn_Y TC1_IRQn
#define CAPTURE_Handler_Y TC1_Handler
#define CAPTURE_ID_Y ID_TC1
#define CAPTURE_PIN_Y 61
#define CAPTURE_CLOCK_SELECTION_Y TC_CMR_TCCLKS_TIMER_CLOCK3

// clock divisors corresponding to CAPTURE_CLOCK_SELECTION
static const uint32_t divisors[5] = { 2, 8, 32, 128, 0 };

volatile uint32_t captured_pulses[4];
volatile uint32_t captured_ra[4];
volatile uint32_t captured_rb[4];
uint32_t frequency[4];
uint32_t duty_cycle[4];
uint32_t active_time[4];

#define ROLL    0
#define PITCH   1

#define YAW   2


// timer interrupt handle
void CAPTURE_Handler_R() {
	if ((TC_GetStatus(CAPTURE_TC_R, CAPTURE_CHANNEL_R) & TC_SR_LDRBS) == TC_SR_LDRBS) {
		captured_pulses[ROLL]++;
		captured_ra[ROLL] = CAPTURE_TC_R->TC_CHANNEL[CAPTURE_CHANNEL_R].TC_RA;
		captured_rb[ROLL] = CAPTURE_TC_R->TC_CHANNEL[CAPTURE_CHANNEL_R].TC_RB;
	}
}

// timer interrupt handle
void CAPTURE_Handler_P() {
	if ((TC_GetStatus(CAPTURE_TC_P, CAPTURE_CHANNEL_P) & TC_SR_LDRBS) == TC_SR_LDRBS) {
		captured_pulses[PITCH]++;
		captured_ra[PITCH] = CAPTURE_TC_P->TC_CHANNEL[CAPTURE_CHANNEL_P].TC_RA;
		captured_rb[PITCH] = CAPTURE_TC_P->TC_CHANNEL[CAPTURE_CHANNEL_P].TC_RB;
	}
}


// timer interrupt handle
void CAPTURE_Handler_Y() {
	if ((TC_GetStatus(CAPTURE_TC_Y, CAPTURE_CHANNEL_Y) & TC_SR_LDRBS) == TC_SR_LDRBS) {
		captured_pulses[YAW]++;
		captured_ra[YAW] = CAPTURE_TC_Y->TC_CHANNEL[CAPTURE_CHANNEL_Y].TC_RA;
		captured_rb[YAW] = CAPTURE_TC_Y->TC_CHANNEL[CAPTURE_CHANNEL_Y].TC_RB;
	}
}




FlightController::FlightController()
{

	// configure the PIO pin as peripheral
	const PinDescription *config_R = &g_APinDescription[CAPTURE_PIN_R];
	PIO_Configure(
		config_R->pPort,
		config_R->ulPinType,
		config_R->ulPin,
		config_R->ulPinConfiguration
		);

	const PinDescription *config_P = &g_APinDescription[CAPTURE_PIN_P];
	PIO_Configure(
		config_P->pPort,
		config_P->ulPinType,
		config_P->ulPin,
		config_P->ulPinConfiguration
		);


	const PinDescription *config_Y = &g_APinDescription[CAPTURE_PIN_Y];
	PIO_Configure(
		config_Y->pPort,
		config_Y->ulPinType,
		config_Y->ulPin,
		config_Y->ulPinConfiguration
		);

	// enable timer peripheral clock
	pmc_enable_periph_clk(CAPTURE_ID_P);
	pmc_enable_periph_clk(CAPTURE_ID_R);
	pmc_enable_periph_clk(CAPTURE_ID_Y);

	// configure the timer
	TC_Configure(CAPTURE_TC_R, CAPTURE_CHANNEL_R,
		CAPTURE_CLOCK_SELECTION_R /* Clock Selection */
		| TC_CMR_LDRA_RISING /* RA Loading: rising edge of TIOA */
		| TC_CMR_LDRB_FALLING /* RB Loading: falling edge of TIOA */
		| TC_CMR_ABETRG /* External Trigger: TIOA */
		| TC_CMR_ETRGEDG_FALLING /* External Trigger Edge: Falling edge */
		);

	TC_Configure(CAPTURE_TC_P, CAPTURE_CHANNEL_P,
		CAPTURE_CLOCK_SELECTION_P /* Clock Selection */
		| TC_CMR_LDRA_RISING /* RA Loading: rising edge of TIOA */
		| TC_CMR_LDRB_FALLING /* RB Loading: falling edge of TIOA */
		| TC_CMR_ABETRG /* External Trigger: TIOA */
		| TC_CMR_ETRGEDG_FALLING /* External Trigger Edge: Falling edge */
		);


	TC_Configure(CAPTURE_TC_Y, CAPTURE_CHANNEL_Y,
		CAPTURE_CLOCK_SELECTION_Y /* Clock Selection */
		| TC_CMR_LDRA_RISING /* RA Loading: rising edge of TIOA */
		| TC_CMR_LDRB_FALLING /* RB Loading: falling edge of TIOA */
		| TC_CMR_ABETRG /* External Trigger: TIOA */
		| TC_CMR_ETRGEDG_FALLING /* External Trigger Edge: Falling edge */
		);

	// configure TC interrupts
	NVIC_DisableIRQ(CAPTURE_IRQn_R);
	NVIC_ClearPendingIRQ(CAPTURE_IRQn_R);
	NVIC_SetPriority(CAPTURE_IRQn_R, 0);
	NVIC_EnableIRQ(CAPTURE_IRQn_R);

	NVIC_DisableIRQ(CAPTURE_IRQn_P);
	NVIC_ClearPendingIRQ(CAPTURE_IRQn_P);
	NVIC_SetPriority(CAPTURE_IRQn_P, 0);
	NVIC_EnableIRQ(CAPTURE_IRQn_P);



	NVIC_DisableIRQ(CAPTURE_IRQn_Y);
	NVIC_ClearPendingIRQ(CAPTURE_IRQn_Y);
	NVIC_SetPriority(CAPTURE_IRQn_Y, 0);
	NVIC_EnableIRQ(CAPTURE_IRQn_Y);


	// enable interrupts
	CAPTURE_TC_R->TC_CHANNEL[CAPTURE_CHANNEL_R].TC_IER = TC_IER_LDRBS;
	CAPTURE_TC_P->TC_CHANNEL[CAPTURE_CHANNEL_P].TC_IER = TC_IER_LDRBS;
	CAPTURE_TC_Y->TC_CHANNEL[CAPTURE_CHANNEL_Y].TC_IER = TC_IER_LDRBS;

	// start timer counter
	CAPTURE_TC_R->TC_CHANNEL[CAPTURE_CHANNEL_R].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	CAPTURE_TC_P->TC_CHANNEL[CAPTURE_CHANNEL_P].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	CAPTURE_TC_Y->TC_CHANNEL[CAPTURE_CHANNEL_Y].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;


	_state = Disarmed;

	_roll.attach(C_APM_ROLL);
	_pitch.attach(C_APM_PITCH);
	_throttle.attach(C_APM_THROTTLE);
	_yaw.attach(C_APM_YAW);

	pinMode(7, INPUT);
	pinMode(6, INPUT);
	pinMode(5, INPUT);
	pinMode(4, INPUT);

	


	_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_throttle.writeMicroseconds(MIN);

	

	_TotalVector.getData()[0] = 50;
	_TotalVector.getData()[1] = 50;
	_JoyVector.getData()[0] = 50;
	_JoyVector.getData()[1] = 50;

	_regReadCount = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::addRegister(volatile MessageBuffer_Passer* newRegister)
{
	switch (newRegister->getID())
	{
	case MB_JOY_XY:
		_XYJoyRegister = newRegister;
		break;
	case MB_JOY_THROTTLE:
		_throttleJoyRegister = newRegister;
		break;
	case MB_JOY_Z:
		_ZJoyRegister = newRegister;
		break;
	case MB_ARM_DISARM:
		_ArmDisarmRegister = newRegister;
		break;
	case MB_COMPENSATOR_VECTOR:
		_CompensationVector = newRegister;
		break;
	case MB_AVOID:
		_AvoidRegister = newRegister;
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

bool FlightController::start()
{
	disarm();
	if (_XYJoyRegister->getID() != MB_JOY_XY ||
		_throttleJoyRegister->getID() != MB_JOY_THROTTLE ||
		_ZJoyRegister->getID() != MB_JOY_Z ||
		_ArmDisarmRegister->getID() != MB_ARM_DISARM)
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool FlightController::run()
{
	active_time[ROLL]= ((captured_rb[ROLL] - captured_ra[ROLL]) * 1000) /((F_CPU / divisors[CAPTURE_CLOCK_SELECTION_R]) / 1000);
	_roll.writeMicroseconds(active_time[ROLL]);

	active_time[PITCH] = ((captured_rb[PITCH] - captured_ra[PITCH]) * 1000) / ((F_CPU / divisors[CAPTURE_CLOCK_SELECTION_R]) / 1000);
	_pitch.writeMicroseconds(active_time[PITCH]);

	active_time[YAW] = ((captured_rb[YAW] - captured_ra[YAW]) * 1000) / ((F_CPU / divisors[CAPTURE_CLOCK_SELECTION_R]) / 1000);
	_yaw.writeMicroseconds(active_time[YAW]);
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::arm()
{
	if (_state == Disarmed)
	{
		// start arm
		_armTime.start(5000);
		_state = Arming;

		_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_yaw.writeMicroseconds(MAX);
		_throttle.writeMicroseconds(MIN);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::disarm()
{
	if (_state == Armed)
	{
		// start disarm
		_armTime.start(3000);
		_state = Disarming;

		_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_yaw.writeMicroseconds(MIN);
		_throttle.writeMicroseconds(MIN);

		_TotalVector.getData()[0] = 50;
		_TotalVector.getData()[1] = 50;
		_JoyVector.getData()[0] = 50;
		_JoyVector.getData()[1] = 50;
	}
}

#endif

#if FLIGHT_MODE == JOYSTICK

FlightController::FlightController()
{
	_state = Disarmed;

	_roll.attach(C_APM_ROLL);
	_pitch.attach(C_APM_PITCH);
	_throttle.attach(C_APM_THROTTLE);
	_yaw.attach(C_APM_YAW);

	_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
	_throttle.writeMicroseconds(MIN);

	_TotalVector.getData()[0] = 50;
	_TotalVector.getData()[1] = 50;
	_JoyVector.getData()[0] = 50;
	_JoyVector.getData()[1] = 50;

	_regReadCount = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::addRegister(volatile MessageBuffer_Passer* newRegister)
{
	switch (newRegister->getID())
	{
	case MB_JOY_XY:
		_XYJoyRegister = newRegister;
		break;
	case MB_JOY_THROTTLE:
		_throttleJoyRegister = newRegister;
		break;
	case MB_JOY_Z:
		_ZJoyRegister = newRegister;
		break;
	case MB_ARM_DISARM:
		_ArmDisarmRegister = newRegister;
		break;
	case MB_COMPENSATOR_VECTOR:
		_CompensationVector = newRegister;
		break;
	case MB_AVOID:
		_AvoidRegister = newRegister;
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

bool FlightController::start()
{
	disarm();
	if (_XYJoyRegister->getID() != MB_JOY_XY ||
		_throttleJoyRegister->getID() != MB_JOY_THROTTLE ||
		_ZJoyRegister->getID() != MB_JOY_Z ||
		_ArmDisarmRegister->getID() != MB_ARM_DISARM)
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------

bool FlightController::run()
{
	// check for state transitions
	switch (_state)
	{
	case Arming:
		if (_armTime.hasTimeOut())
		{
			_state = Armed;

			_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_throttle.writeMicroseconds(MIN);
		}
		break;
	case Disarming:
		if (_armTime.hasTimeOut())
		{
			_state = Disarmed;

			_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_yaw.writeMicroseconds(MIN + ((MAX - MIN) / 2));
			_throttle.writeMicroseconds(MIN);
		}
		break;
	}

	switch (_state)
	{
	case Disarmed:
		if (_ArmDisarmRegister->getData()[0] != 0)
		{
			arm();
		}
		break;
	case Armed:
		if (_ArmDisarmRegister->getData()[0] == 0)
		{
			disarm();
		}
		break;
	}


	// update joystick values
	if (_state == Armed)
	{
		_JoyVector.getData()[0] = _XYJoyRegister->getData()[0];
		_JoyVector.getData()[1] = _XYJoyRegister->getData()[1];

		int roll;
		int pitch;

		if (_AvoidRegister->getData()[0] == 0)
		{
			roll = _XYJoyRegister->getData()[0];
			pitch = _XYJoyRegister->getData()[1];
		}
		else
		{
			roll = (((_XYJoyRegister->getData()[0] - 50) * 2) + ((_CompensationVector->getData()[0] - 50) * 2)) / 2 + 50;
			pitch = (((_XYJoyRegister->getData()[1] - 50) * 2) + ((_CompensationVector->getData()[1] - 50) * 2)) / 2 + 50;
		}

		_roll.writeMicroseconds(roll* MULTIPLYER + MIN);
		_pitch.writeMicroseconds(pitch* MULTIPLYER + MIN);
		_yaw.writeMicroseconds(_ZJoyRegister->getData()[0] * MULTIPLYER + MIN);
		_throttle.writeMicroseconds(_throttleJoyRegister->getData()[0] * MULTIPLYER + MIN);

		_TotalVector.getData()[0] = roll;
		_TotalVector.getData()[1] = pitch;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::arm()
{
	if (_state == Disarmed)
	{
		// start arm
		_armTime.start(5000);
		_state = Arming;

		_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_yaw.writeMicroseconds(MAX);
		_throttle.writeMicroseconds(MIN);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------

void FlightController::disarm()
{
	if (_state == Armed)
	{
		// start disarm
		_armTime.start(3000);
		_state = Disarming;

		_roll.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_pitch.writeMicroseconds(MIN + ((MAX - MIN) / 2));
		_yaw.writeMicroseconds(MIN);
		_throttle.writeMicroseconds(MIN);

		_TotalVector.getData()[0] = 50;
		_TotalVector.getData()[1] = 50;
		_JoyVector.getData()[0] = 50;
		_JoyVector.getData()[1] = 50;
	}
}

#endif