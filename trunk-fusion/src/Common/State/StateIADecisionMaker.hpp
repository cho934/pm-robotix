/*!
 * \file
 * \brief Définition de la classe StateIADecisionMaker.
 */

#ifndef STATEIADECISIONMAKER_HPP
#define	STATEIADECISIONMAKER_HPP

#include <string>

#include "../../Log/LoggerFactory.hpp"
#include "AAutomateState.hpp"

class StateIADecisionMaker: public AAutomateState
{
public:
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("StateIADecisionMaker");
		return instance;
	}

public:

	StateIADecisionMaker()
	{
	}
	virtual std::string name()
	{
		return "StateIADecisionMaker";
	}
	virtual ~StateIADecisionMaker()
	{
	}

	virtual IAutomateState* execute(Robot& robot, void * data);

	void IASetupTableTest();
	void IASetupHomologation();
	void IASetupMatches();

};

#endif
