/*!
 * \file
 * \brief Définition de la classe ArduinoTest.
 */

#ifndef ROBOTTEST_ARDUINOTEST_HPP
#define	ROBOTTEST_ARDUINOTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test de communication Arduino.
 */
class ArduinoTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ArduinoTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::ArduinoTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ArduinoTest()
			: pmx::ConsoleUnitTest("ArduinoTest : Communicate with the arduino board")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ArduinoTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}

#endif
