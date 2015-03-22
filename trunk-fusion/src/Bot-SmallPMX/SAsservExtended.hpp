/*
 * AsservExtended.hpp
 *
 *  Created on: Oct 2, 2014
 *      Author: pmx
 */

#ifndef PMX_S_ASSERVEXTENDED_HPP_
#define PMX_S_ASSERVEXTENDED_HPP_

#include "../Common/Asserv/Asserv.hpp"
#include "../Common/Asserv/EncoderControl.hpp"

class SAsservExtended: public Asserv
{
private:

	/*!
	 * \brief LED Bar.
	 */
	EncoderControl encoders_;

public:
	SAsservExtended() :
			encoders_(*this)
	{
	}

	/*!
	 * \brief Cette methode retourne l'objet EncoderControl.
	 * \return encoders_.
	 */
	inline EncoderControl & encoders()
	{
		return encoders_;
	}
};

#endif
