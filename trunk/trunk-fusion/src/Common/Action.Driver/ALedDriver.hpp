#ifndef ALEDDRIVER_HPP_
#define ALEDDRIVER_HPP_

#define LD_ORANGE 3

class ALedDriver
{

public:
	/*!
	 * \brief LedDriver instance creation.
	 */
	static ALedDriver * create(int nb);

	/*!
	 * \brief Set led value.
	 *
	 * \param position
	 * 				The position of the ledbar.
	 * \param aValue
	 * 				The color of the led.
	 */
	virtual void set(int position, int aValue) = 0;

	/*!
	 * \brief Destructor.
	 */
	virtual ~ALedDriver()
	{}

protected:

	/*!
	 * \brief Constructor.
	 */
	ALedDriver()
	{}

};

#endif
