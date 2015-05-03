#ifndef EV3_DETECTIONSENSORDRIVER_HPP_
#define EV3_DETECTIONSENSORDRIVER_HPP_

#include "../Common/Action.Driver/ADetectSensorDriver.hpp"
#include "../Log/LoggerFactory.hpp"
#include "ev3dev.h"

using namespace std;
using namespace ev3dev;

class DetectionSensorDriver: public ADetectSensorDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref DetectionSensorDriver(EV3).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("DetectionSensorDriver.EV3");
		return instance;
	}

	infrared_sensor ir_;

public:


	/*!
	 * \brief Constructor.
	 */
	DetectionSensorDriver();

	/*!
	 * \brief Destructor.
	 */
	virtual ~DetectionSensorDriver();

	virtual int getDistanceMM();

};

#endif
