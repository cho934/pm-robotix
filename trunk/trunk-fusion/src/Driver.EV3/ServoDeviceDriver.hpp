#ifndef EV3_SERVODEVICEDRIVER_HPP_
#define EV3_SERVODEVICEDRIVER_HPP_

#include "../Common/Action.Driver/AServoDeviceDriver.hpp"
#include "../Log/LoggerFactory.hpp"
#include "ev3dev.h"

using namespace std;
using namespace ev3dev;

class ServoDeviceDriver: public AServoDeviceDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoDeviceDriver(EV3).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("ServoDeviceDriver.EV3");
		return instance;
	}

	int connected_;
	large_motor _servo_device;

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

	virtual void setMotorPosition(int pos, int timems);

	virtual long getInternalEncoder();

	virtual void resetEncoder(int pos);

	virtual void stopMotor();

	virtual int getMotorCurrent();

	virtual void enableHardRegulation(bool enable);

};

#endif
