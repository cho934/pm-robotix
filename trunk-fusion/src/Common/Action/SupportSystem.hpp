#ifndef SUPPORT_TRACKSYSTEM_HPP_
#define SUPPORT_TRACKSYSTEM_HPP_

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "AActionsElement.hpp"
#include "../Action.Driver/AServoDeviceDriver.hpp"

class SupportSystem: public AActionsElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref SupportSystem.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("SupportSystem");
		return instance;
	}

	AServoDeviceDriver* servodevicedriver;

public:

	/*!
	 * \brief Constructor.
	 */
	SupportSystem(Actions & actions);

	/*!
	 * \brief Destructor.
	 */
	~SupportSystem();

	/*!
	 * \brief incline.
	 */
	void incline(int power, int timems);

	/*!
	 * \brief redresse.
	 */
	void straighten(int power, int timems);

	/*!
	 * \brief setPosition.
	 */
	void resetPosition(int pos);

	/*!
	 * \brief stop motor.
	 */
	void stopMotor();

};

#endif
