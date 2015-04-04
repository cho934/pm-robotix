#ifndef TRACKSYSTEM_HPP_
#define TRACKSYSTEM_HPP_

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "AActionsElement.hpp"
#include "../Action.Driver/AMotorDeviceDriver.hpp"

class TrackSystem: public AActionsElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref TrackSystem.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("TrackSystem");
		return instance;
	}

	AMotorDeviceDriver* motordriver;

public:

	/*!
	 * \brief Constructor.
	 */
	TrackSystem(Actions & actions);

	/*!
	 * \brief Destructor.
	 */
	~TrackSystem();

	/*!
	 * \brief moveForward.
	 */
	void moveForward(int power, int timems);

	/*!
	 * \brief stop motor.
	 */
	void stopMotor();

};

#endif
