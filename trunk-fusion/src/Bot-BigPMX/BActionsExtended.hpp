#ifndef PMX_B_ACTIONSEXTENDED_HPP
#define PMX_B_ACTIONSEXTENDED_HPP

#include "../Action/LedBar.hpp"
#include "../Action/Actions.hpp"

class BActionsExtended: public Actions
{
public:

	/*!
	 * \brief other LED Bar element.
	 */
	LedBar ledbar_;


	BActionsExtended() :
				ledbar_(8)
		{
		}
};

#endif

