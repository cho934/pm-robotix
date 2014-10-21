#ifndef PMX_S_ACTIONSEXTENDED_HPP
#define PMX_S_ACTIONSEXTENDED_HPP

#include "../Action/LedBar.hpp"
#include "../Action/Actions.hpp"

class SActionsExtended: public Actions
{
public:

	/*!
	 * \brief LED Bar.
	 */
	LedBar ledbar_;


	SActionsExtended() :
			ledbar_(2)
	{
	}

};

#endif

