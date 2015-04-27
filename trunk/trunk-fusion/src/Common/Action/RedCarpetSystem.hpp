#ifndef REDCARPETSYSTEM_HPP_
#define REDCARPETSYSTEM_HPP_

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "AActionsElement.hpp"
#include "../Action.Driver/AServoDriver.hpp"

class RedCarpetSystem: public AActionsElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref RedCarpetSystem.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("RedCarpetSystem");
		return instance;
	}

	AServoDriver* servodriver;

public:

	/*!
	 * \brief Constructor.
	 */
	RedCarpetSystem(Actions & actions);

	/*!
	 * \brief Destructor.
	 */
	~RedCarpetSystem();

	void leftDeploy();

	void rightDeploy();

	void releaseLeft();
	void releaseRight();

	void holdLeft();
	void holdRight();

	void releaseAll();
	void holdAll();

};

#endif
