
#ifndef DETECTIONSENSOR_HPP_
#define DETECTIONSENSOR_HPP_

#include "../../Log/LoggerFactory.hpp"
#include "AActionsElement.hpp"

#include "../Action.Driver/ADetectSensorDriver.hpp"

#include "../Utils/Macro.hpp"



class DetectionSensor: public AActionsElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref DetectionSensor.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("DetectionSensor");
		return instance;
	}


public:
	ADetectSensorDriver* detectsensordriver;

	/*!
	 * \brief Constructor.
	 */
	DetectionSensor(Actions & actions);

	/*!
	 * \brief Destructor.
	 */
	~DetectionSensor();

	int getDistanceMM();

	void monitor(int nb);

	bool isAdversaryDetected();

};



#endif
