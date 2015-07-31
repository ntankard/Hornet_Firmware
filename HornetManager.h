#pragma once
#include "Error.h"

// forward declare to prevent circular dependancy
class Coms;
class ComsEncoder;
class AccGyro;

enum State{Init,Connect};

class HornetManager
{
public:

	/**
	 * \fn	HornetManager::HornetManager();
	 *
	 * \brief	Creates the static objects in the manager, certain componets must be added after constuction then setup can run
	 *
	 * \author	Nicholas
	 * \date	29/07/2015
	 */
	HornetManager();

	/**
	 * \fn	void HornetManager::start();
	 *
	 * \brief	Complets the construction after all object have been created and attached
	 *
	 * \author	Nicholas
	 * \date	1/08/2015
	 */
	void start();

	/**
	 * \fn	void HornetManager::attachComs(Coms* theComs);
	 *
	 * \brief	Attach a pre constructed coms object that holds a refrence to this manager instance
	 *
	 * \author	Nicholas
	 * \date	29/07/2015
	 *
	 * \param [in,out]	theComs	If non-null, the coms.
	 */
	void attachComs(Coms* theComs);

	void attachComsEncoder(ComsEncoder* theComsEncoder);

	void attachAccGyro(AccGyro* theAccGyro);

	void newAccGyro(float accel[3], float gyro[3]);

	void run();
private:

	State _state;

	Coms* _coms;
	ComsEncoder* _comsEncoder;
	AccGyro* _accGyro;
	Error* _e;
};

