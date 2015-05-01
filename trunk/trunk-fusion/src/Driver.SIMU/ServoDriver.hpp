#ifndef SIMU_SERVODRIVER_HPP_
#define SIMU_SERVODRIVER_HPP_

#include "../Common/Action.Driver/AServoDriver.hpp"
#include "../Log/LoggerFactory.hpp"


using namespace std;



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
		static const logs::Logger & instance = logs::LoggerFactory::logger("ServoDriver.SIMU");
		return instance;
	}

	int connected_;


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
