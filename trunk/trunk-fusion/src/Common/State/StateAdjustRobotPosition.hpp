/*!
 * \file
 * \brief Définition de la classe StateAdjustRobotPosition.
 */

#ifndef STATEADJUSTROBOTPOSITION_HPP
#define	STATEADJUSTROBOTPOSITION_HPP

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "AAutomateState.hpp"

class StateAdjustRobotPosition: public AAutomateState
{
private:

	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger(
				"StateAdjustRobotPosition");
		return instance;
	}

public:

	StateAdjustRobotPosition()
	{
	}
	virtual std::string name()
	{
		return "StateAdjustRobotPosition";
	}
	virtual ~StateAdjustRobotPosition()
	{
	}

	virtual IAutomateState* execute(Robot& robot, void * data);
};

#endif
