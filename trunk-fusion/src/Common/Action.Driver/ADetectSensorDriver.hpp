#ifndef ADETECTSENSORDRIVER_HPP_
#define ADETECTSENSORDRIVER_HPP_

#include "../Utils/Macro.hpp"

class ADetectSensorDriver
{

public:
	/*!
	 * \brief ADetectSensorDriver instance creation.
	 */
	static ADetectSensorDriver * create();

	/*
	 *\brief getDistanceMM.
	 */
	virtual int getDistanceMM() = 0;

	/*!
	 * \brief Destructor.
	 */
	virtual ~ADetectSensorDriver()
	{
	}

protected:

	/*!
	 * \brief Constructor.
	 */
	ADetectSensorDriver()
	{
	}

};

#endif
