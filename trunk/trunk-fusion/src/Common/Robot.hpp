#ifndef COMMON_ROBOT_HPP_
#define COMMON_ROBOT_HPP_

#include "../Log/LoggerFactory.hpp"
#include "Action/Actions.hpp"
#include "Utils/Chronometer.hpp"

class ConsoleManager;

enum RobotColor
{
	PMXNOCOLOR, PMXYELLOW, PMXGREEN
};

class Robot
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref Robot.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("Robot");
		return instance;
	}

	utils::Chronometer chrono_;

	RobotColor myColor_;

public:

	//Action => RobotElement
	Actions actions;

	//Asserv

	//IA

	/*!
	 * \brief Constructeur de la classe.
	 */
	Robot();

	/*!
	 * \brief Destructor.
	 */
	virtual inline ~Robot()
	{
	}

	void operator=(Robot const&); // Don't implement

	/*!
	 * \brief Cette methode retourne l'objet de manipulation du chronometer.
	 * \return Le chronometer.
	 */
	inline utils::Chronometer & chrono()
	{
		return chrono_;
	}

	/*!
	 * \brief Retourne la couleur du robot.
	 */
	inline RobotColor getMyColor() const
	{
		return myColor_;
	}

	/*!
	 * \brief Enregistre la couleur du robot.
	 */
	inline void setMyColor(RobotColor color)
	{
		this->myColor_ = color;
	}

	/*!
	 * \brief Start the robot (console for tests or main program)..
	 */
	void start(ConsoleManager manager, int argc, char** argv);

};

#endif
