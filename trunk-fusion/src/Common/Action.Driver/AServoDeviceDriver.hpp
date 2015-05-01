/* pour les moteurs utilisés en mode servomotor.
 *
 */
#ifndef ASERVODEVICEDRIVER_HPP_
#define ASERVODEVICEDRIVER_HPP_

class AServoDeviceDriver
{

public:

	/*!
	 * \brief single instance creation.
	 */
	static AServoDeviceDriver * create();

	/*!
	 * \brief Destructor.
	 */
	virtual ~AServoDeviceDriver()
	{
	}

	/*!
	 * \brief Constructor.
	 */
	AServoDeviceDriver()
	{
	}

	virtual void setMotorPosition(int pos, int timems, int power) = 0;

	virtual long getInternalEncoder()= 0;

	virtual void resetEncoder(int pos)= 0;

	virtual void stopMotor()= 0;

	virtual int getMotorCurrent()= 0;

	virtual void enableHardRegulation(bool enable)= 0;

private:

protected:

};

#endif
