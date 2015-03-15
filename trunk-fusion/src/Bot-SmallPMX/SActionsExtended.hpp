#ifndef PMX_S_ACTIONSEXTENDED_HPP_
#define PMX_S_ACTIONSEXTENDED_HPP_

#include "../Common/Action/LedBar.hpp"
#include "../Common/Action/Actions.hpp"

class SActionsExtended: public Actions
{
private:

	/*!
	 * \brief LED Bar.
	 */
	LedBar ledbar_;

public:
	SActionsExtended() :
			ledbar_(*this, 2)
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

