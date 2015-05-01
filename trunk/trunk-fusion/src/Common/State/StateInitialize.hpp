/*!
 * \file
 * \brief Définition de la classe StateInitialize.
 */

#ifndef STATEINITIALIZE_HPP
#define	STATEINITIALIZE_HPP

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "AAutomateState.hpp"

class StateInitialize: public AAutomateState
{
private:

	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("StateInitialize");
		return instance;
	}

public:

	StateInitialize()
	{
	}

	virtual ~StateInitialize()
	{
	}

	virtual std::string name()
	{
		return "StateInitialize";
	}
	virtual IAutomateState* execute(Robot& robot, void * data);
};

#endif
