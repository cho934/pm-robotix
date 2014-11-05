#ifndef ACTIONDRIVER_HPP_
#define ACTIONDRIVER_HPP_

class ActionDriver
{

public:

	int example1;

#ifdef SIMU
	int exampleSimu;
#endif

	virtual void driverSetPin(int numled, int value);

	/*!
	 * \brief Constructor.
	 */
	ActionDriver()
	{
		example1 = 0;
#ifdef SIMU
		exampleSimu=0;
#endif
	}

	/*!
	 * \brief Destructor.
	 */
	virtual ~ActionDriver()
	{
	}

};

#endif
