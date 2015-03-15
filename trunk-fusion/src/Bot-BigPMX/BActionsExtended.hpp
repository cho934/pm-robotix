#ifndef PMX_B_ACTIONSEXTENDED_HPP_
#define PMX_B_ACTIONSEXTENDED_HPP_

#include "../Common/Action/LedBar.hpp"
#include "../Common/Action/Actions.hpp"

class BActionsExtended: public Actions
{
private:

	/*!
	 * \brief other LED Bar element.
	 */
	LedBar ledbar_;

public:
	BActionsExtended() :
			ledbar_(*this, 8)
	{
	}

	/*!
	 * \brief Cette methode retourne l'objet ledbar.
	 * \return ledbar_.
	 */
	inline LedBar & ledbar()
	{
		return ledbar_;
	}
};

#endif

