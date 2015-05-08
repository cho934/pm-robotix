#ifndef PMX_S_ROBOTEXTENDED_HPP_
#define PMX_S_ROBOTEXTENDED_HPP_

#include "../Common/Robot.hpp"
#include "SActionsExtended.hpp"
#include "SAsservExtended.hpp"



class SRobotExtended: public Robot
{
public:

	static SRobotExtended & instance()
	{
		static SRobotExtended instance;
		return instance;
	}

	//on etend les actions possibles
	//SActionsExtended* actions;
	//SAsservExtended*	asserv;

private:
	SAsservExtended* asserv_;
	SActionsExtended* actions_;

	SRobotExtended();

public:

	~SRobotExtended()
	{

	}

	inline SAsservExtended& asserv()
	{

		SAsservExtended& r_asserv = *asserv_;
		return r_asserv;
	}

	inline SActionsExtended& actions()
	{

		SActionsExtended& r_actions = *actions_;
		return r_actions;
	}

	void stop();
};

#endif

