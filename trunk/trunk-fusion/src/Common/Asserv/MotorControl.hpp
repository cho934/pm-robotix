//utilise directement les moteurs et leurs fonctionnalités (internes ou via une carte d'asserv).

#ifndef COMMON_ASSERV_MOTORCONTROL_HPP_
#define COMMON_ASSERV_MOTORCONTROL_HPP_

#include "../../Log/LoggerFactory.hpp"
#include "AAsservElement.hpp"

#include "../Asserv.Driver/AAsservDriver.hpp"

class MotorControl: public AAsservElement
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref MotorControl.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("MotorControl");
		return instance;
	}

	AAsservDriver* asservdriver;

public:

	/*!
	 * \brief Constructor.
	 */
	MotorControl(Asserv & asserv);

	/*!
	 * \brief Destructor.
	 */
	~MotorControl();

	/*!
	 * \brief runMotorLeft by power -900/+900.
	 */
	void runMotorLeft(int power, int timeus);
	/*!
	 * \brief runMotorRight by power -900/+900.
	 */
	void runMotorRight(int power, int timeus);

	/*!
	 * \brief stop both motors.
	 */
	void stopMotors();

	//motorLeft(speed)



	//moveForward(power)
	//moveForward(speed)
	//moveForwardWithRamp(int distmm)

	//turn()
	//turnLeft(float deg)
	//turnRight(float deg)
};

#endif
