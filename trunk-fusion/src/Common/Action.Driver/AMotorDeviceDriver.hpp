#ifndef AMOTORDEVICEDRIVER_HPP_
#define AMOTORDEVICEDRIVER_HPP_

class AMotorDeviceDriver
{

public:

	/*!
	 * \brief single instance creation.
	 */
	static AMotorDeviceDriver * create();

	/*!
	 * \brief Destructor.
	 */
	virtual ~AMotorDeviceDriver()
	{
	}

	/*!
	 * \brief Constructor.
	 */
	AMotorDeviceDriver()
	{
	}

	virtual void setMotorPower(int power, int timems) = 0;

	virtual long getInternalEncoder()= 0;

	virtual void resetEncoder()= 0;

	virtual void stopMotor()= 0;

	virtual int getMotorCurrent()= 0;


	virtual void enableHardRegulation(bool enable)= 0;

private:

protected:

};

#endif
