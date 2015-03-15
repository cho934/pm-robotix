#ifndef PMX_S_ACTIONSEXTENDED_HPP_
#define PMX_S_ACTIONSEXTENDED_HPP_

#include "../Common/Action/LedBar.hpp"
#include "../Common/Action/SoundBar.hpp"
#include "../Common/Action/Actions.hpp"

class SActionsExtended: public Actions
{
private:

	/*!
	 * \brief LED Bar.
	 */
	LedBar ledbar_;

	SoundBar soundbar_;

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

	/*!
	 * \brief Cette methode retourne l'objet soundBar.
	 * \return ledbar_.
	 */
	inline SoundBar & soundbar()
	{
		return soundbar_;
	}

};

#endif

