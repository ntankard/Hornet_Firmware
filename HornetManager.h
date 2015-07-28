#pragma once

// forward declare to prevent circular dependancy
class Coms;

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

	void run();
private:
	Coms* _coms;
};

