
#ifndef PMX_BOTBIGPMX_ASSERVEXTENDED_HPP_
#define PMX_BOTBIGPMX_ASSERVEXTENDED_HPP_

#include "../Common/Asserv/Asserv.hpp"
#include "../Common/Asserv/EncoderControl.hpp"

class BAsservExtended: public Asserv
{
private:

	/*!
	 * \brief LED Bar.
	 */
	EncoderControl encoders_;

public:
	BAsservExtended() :
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
