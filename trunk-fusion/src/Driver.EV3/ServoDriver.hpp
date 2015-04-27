#ifndef EV3_SERVODRIVER_HPP_
#define EV3_SERVODRIVER_HPP_

#include "../Common/Action.Driver/AServoDriver.hpp"
#include "../Log/LoggerFactory.hpp"
#include "ev3dev.h"

using namespace std;
using namespace ev3dev;

/*
const port_type SV0  { "0" };  //!< servo sv0
const port_type SV1  { "1" };  //!< servo sv1
const port_type SV6  { "6" };  //!< servo sv6
const port_type SV7  { "7" };  //!< servo sv7
*/

#ifndef FSTREAM_CACHE_SIZE
#define FSTREAM_CACHE_SIZE 16
#endif

class ServoDriver: public AServoDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoDriver(EV3).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("ServoDriver.EV3");
		return instance;
	}

	int connected_;
	//servo_motor m_;

	char* positionOpFileName_;

	std::string _path;
	std::string _pathSV1;
	std::string _pathSV8;

	void set_attr_int(const std::string &name, int value);
	void set_attr_string(const std::string &name, const std::string &value);

protected:

public:
	/*!
	 * \brief Constructor.
	 */
	ServoDriver();

	/*!
	 * \brief Destructor.
	 */
	virtual inline ~ServoDriver()
	{
	}

	virtual void hold(int servoId);

	virtual void setPosition(int servoId, int pos);

	virtual void release(int servoId);

};

#endif
