#ifndef SIMU_SERVODEVICEDRIVER_HPP_
#define SIMU_SERVODEVICEDRIVER_HPP_

#include "../Common/Action.Driver/AServoDeviceDriver.hpp"
#include "../Log/LoggerFactory.hpp"

using namespace std;

class ServoDeviceDriver: public AServoDeviceDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoDeviceDriver(EV3).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger(
				"ServoDeviceDriver.SIMU");
		return instance;
	}

	int connected_;

protected:

public:
	/*!
	 * \brief Constructor.
	 */
	ServoDeviceDriver();

	/*!
	 * \brief Destructor.
	 */
	virtual inline ~ServoDeviceDriver()
	{
	}

	virtual void setMotorPosition(int pos, int timems, int power);

	virtual long getInternalEncoder();

	virtual void resetEncoder(int pos);

	virtual void stopMotor();

	virtual int getMotorCurrent();

	virtual void enableHardRegulation(bool enable);

};

#endif
