#ifndef EV3_ASSERVDRIVER_HPP_
#define EV3_ASSERVDRIVER_HPP_

#include "../Common/Asserv.Driver/AAsservDriver.hpp"
#include "../Common/LogAppender/LoggerFactory.hpp"
#include "../Common/Utils/Macro.hpp"
#include "ev3dev.h"

using namespace std;
using namespace ev3dev;

class AsservDriver: public AAsservDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref AsservDriver(EV3).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("AsservDriver.EV3");
		return instance;
	}
protected:
  large_motor     _motor_left;
  large_motor     _motor_right;

public:

	virtual void setMotorLeftPower(int power, int time);
	virtual void setMotorRightPower(int power, int time);

	virtual long getLeftExternalEncoder();
	virtual long getRightExternalEncoder();

	virtual long getLeftInternalEncoder();
	virtual long getRightInternalEncoder();

	virtual void stopMotorLeft();
	virtual void stopMotorRight();

	virtual int getMotorLeftCurrent();
	virtual int getMotorRightCurrent();

	virtual void enableHardRegulation(bool enable);

	/*!
	 * \brief Constructor.
	 */
	AsservDriver();

	/*!
	 * \brief Destructor.
	 */
	virtual ~AsservDriver();

};

#endif
