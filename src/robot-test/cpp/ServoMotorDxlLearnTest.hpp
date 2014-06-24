/*!
 * \file
 * \brief Définition de la classe ServoMotorDxlLearnTest.
 */

#ifndef ROBOTTEST_SERVOMOTORLEARNTEST_HPP
#define	ROBOTTEST_SERVOMOTORLEARNTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test d'aprentissage des positions des AX12..
 */
class ServoMotorDxlLearnTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoMotorDxlLearnTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::ServoMotorDxlLearnTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ServoMotorDxlLearnTest()
			: pmx::ConsoleUnitTest("ServoMotorDxlLearnTest : learn AX-12 position")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ServoMotorDxlLearnTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}

#endif
