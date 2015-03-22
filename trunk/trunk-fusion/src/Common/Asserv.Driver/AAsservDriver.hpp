#ifndef AASSERVDRIVER_HPP_
#define AASSERVDRIVER_HPP_

class AAsservDriver
{

public:

	/*!
	 * \brief instance creation.
	 */
	static AAsservDriver * create();


	virtual void setMotorLeftPower(int power, int timems) = 0;
	virtual void setMotorRightPower(int power, int timems)= 0;

	virtual long getLeftExternalEncoder()= 0;
	virtual long getRightExternalEncoder()= 0;

	virtual long getLeftInternalEncoder()= 0;
	virtual long getRightInternalEncoder()= 0;

	virtual void stopMotorLeft()= 0;
	virtual void stopMotorRight()= 0;

	virtual int getMotorLeftCurrent()= 0;
	virtual int getMotorRightCurrent()= 0;

	virtual void enableHardRegulation(bool enable)= 0;


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
