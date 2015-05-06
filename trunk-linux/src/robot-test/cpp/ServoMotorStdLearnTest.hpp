/*!
 * \file
 * \brief Définition de la classe ServoMotorStdLearnTest.
 */

#ifndef ROBOTTEST_SERVOMOTORSTDLEARNTEST_HPP
#define	ROBOTTEST_SERVOMOTORSTDLEARNTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test d'aprentissage des positions des servos..
 */
class ServoMotorStdLearnTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorStdLearnTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::ServoMotorStdLearnTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ServoMotorStdLearnTest()
			: pmx::ConsoleUnitTest("ServoMotorStdLearnTest : learn servo position")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ServoMotorStdLearnTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}

#endif
