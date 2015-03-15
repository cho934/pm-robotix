#ifndef AASSERVDRIVER_HPP_
#define AASSERVDRIVER_HPP_

class AAsservDriver
{

public:

	/*!
	 * \brief instance creation.
	 */
	static AAsservDriver * create(int nb);

	virtual void function(int value);

	/*!
	 * \brief Destructor.
	 */
	virtual ~AAsservDriver()
	{
	}

protected:

	/*!
	 * \brief Constructor.
	 */
	AAsservDriver()
	{

	}

};

#endif
