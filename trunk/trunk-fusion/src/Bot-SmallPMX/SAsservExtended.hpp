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
#include "../Common/Asserv/MotorControl.hpp"

class SAsservExtended: public Asserv
{
private:

	/*!
	 * \brief Left and Right Encoder.
	 */
	EncoderControl encoders_;

	MotorControl motors_;

public:
	SAsservExtended() :
			encoders_(*this), motors_(*this)
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

	/*!
	 * \brief Cette methode retourne l'objet MotorControl.
	 * \return motors_.
	 */
	inline MotorControl & motors()
	{
		return motors_;
	}
};

#endif
