#ifndef EV3_MOTORDEVICEDRIVER_HPP_
#define EV3_MOTORDEVICEDRIVER_HPP_

#include "../Common/Action.Driver/AMotorDeviceDriver.hpp"
#include "../Log/LoggerFactory.hpp"
#include "ev3dev.h"

using namespace std;
using namespace ev3dev;

class MotorDeviceDriver: public AMotorDeviceDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref MotorDeviceDriver(EV3).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("MotorDeviceDriver.EV3");
		return instance;
	}

	int connected_;
	large_motor _motor_device;

protected:

public:
	/*!
	 * \brief Constructor.
	 */
	MotorDeviceDriver();

	/*!
	 * \brief Destructor.
	 */
	virtual inline ~MotorDeviceDriver()
	{
	}

	virtual void setMotorPower(int power, int timems);

	virtual long getInternalEncoder();

	virtual void resetEncoder();

	virtual void stopMotor();

	virtual int getMotorCurrent();

	virtual void enableHardRegulation(bool enable);

};

#endif
