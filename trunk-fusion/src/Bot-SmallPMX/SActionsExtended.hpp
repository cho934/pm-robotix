#ifndef PMX_S_ACTIONSEXTENDED_HPP_
#define PMX_S_ACTIONSEXTENDED_HPP_

#include "../Common/Action/LedBar.hpp"
#include "../Common/Action/SoundBar.hpp"
#include "../Common/Action/Actions.hpp"
#include "../Common/Action/TrackSystem.hpp"

class SActionsExtended: public Actions
{
private:

	/*!
	 * \brief LED Bar.
	 */
	LedBar ledbar_;

	/*!
	 * \brief Sound Bar.
	 */
	SoundBar soundbar_;

	/*!
	 * \brief TrackSystem.
	 */
	TrackSystem tracksystem_;

public:
	SActionsExtended() :
			ledbar_(*this, 2)
			, soundbar_(*this)
			, tracksystem_(*this)
	{
	}

	/*!
	 * \brief Cette methode retourne l'objet ledbar.
	 * \return ledbar_.
	 */
	inline LedBar & ledBar()
	{
		return ledbar_;
	}

	/*!
	 * \brief Cette methode retourne l'objet soundBar.
	 * \return soundbar_.
	 */
	inline SoundBar & soundBar()
	{
		return soundbar_;
	}

	/*!
	 * \brief Cette methode retourne l'objet TrackSystem.
	 * \return tracksystem_.
	 */
	inline TrackSystem & trackSystem()
	{
		return tracksystem_;
	}

};

#endif

