#ifndef REDCARPETSYSTEM_HPP_
#define REDCARPETSYSTEM_HPP_

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "AActionsElement.hpp"
#include "../Action.Driver/AServoDriver.hpp"

#define LEFT_CARPET 8
#define RIGHT_CARPET 1

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

	void leftDeploy(int debug = 0);

	void rightDeploy(int debug = 0);

	void releaseLeft();
	void releaseRight();

	void holdLeft();
	void holdRight();

	void releaseAll();
	void holdAll();

};

#endif
