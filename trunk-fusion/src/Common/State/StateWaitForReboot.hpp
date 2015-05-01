/*!
 * \file
 * \brief Définition de la classe StateWaitForReboot.
 */

#ifndef STATEWAITFORREBOOT_HPP
#define	STATEWAITFORREBOOT_HPP

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "AAutomateState.hpp"

class StateWaitForReboot: public AAutomateState
{
private:

	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("StateWaitForReboot");
		return instance;
	}

public:

	StateWaitForReboot()
	{
	}

	virtual ~StateWaitForReboot()
	{
	}

	virtual IAutomateState* execute(Robot& robot, void * data);

	virtual std::string name()
	{
		return "StateWaitForReboot";
	}
};

#endif
