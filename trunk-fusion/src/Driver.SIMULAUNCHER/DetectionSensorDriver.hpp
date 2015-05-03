#ifndef SIMULAUNCHER_DETECTIONSENSORDRIVER_HPP_
#define SIMULAUNCHER_DETECTIONSENSORDRIVER_HPP_

#include "../Common/Action.Driver/ADetectSensorDriver.hpp"
#include "../Log/LoggerFactory.hpp"


using namespace std;


class DetectionSensorDriver: public ADetectSensorDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref DetectionSensorDriver(SIMULAUNCHER).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("DetectionSensorDriver.SIMULAUNCHER");
		return instance;
	}


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
