#ifndef ASSERV_HPP_
#define ASSERV_HPP_

#include "../../Log/LoggerFactory.hpp"
#include "EncoderControl.hpp"
#include "MotorControl.hpp"

class Asserv
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref Asserv.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("Asserv");
		return instance;
	}

	/*!
	 * \brief Left and Right Encoders.
	 */
	EncoderControl encoders_;

	/*!
	 * \brief Left and Right Motors.
	 */
	MotorControl motors_;

	long distTicks_;

	bool adversaryDetected_;

	float entraxe_; //en mm

public:
	float diam_;  //en mm
	/*!
	 * \brief Constructor.
	 */
	Asserv();

	/*!
	 * \brief Destructor.
	 */
	~Asserv()
	{
	}

	/*!
	 * \brief Cette methode retourne l'objet EncoderControl.
	 * \return encoders_.
	 */
	inline EncoderControl & encoders()
	{
		return encoders_;
	}

	/*!
	 * \brief Cette methode retourne l'objet MotorControl.
	 * \return motors_.
	 */
	inline MotorControl & motors()
	{
		return motors_;
	}

	inline void setAdversaryDetected(bool b)
	{
		adversaryDetected_ = b;
	}

	void moveDTime(int power, int timems);

	void moveD(long destTick, long restTick, int power);
	long moveDWaitTrajectory(); //return le reste à parcourir

	void turn(float degree, int timems);
	void turnLeft(float degree, int timems);
	void turnRight(float degree, int timems);
	void turnRightTime(int power, int timems);
	void turnLeftTime(int power, int timems);

	void emergencyStop();

	/*!
	 * \brief Active les actions.
	 *
	 * Cette méthode lance le thread gérant le AsservManager.
	 */
	//void start();
	/*!
	 * \brief Arrete le robot et libère les ressources associés.
	 */
	//void stop();
};

#endif
