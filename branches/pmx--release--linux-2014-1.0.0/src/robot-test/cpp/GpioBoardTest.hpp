/*!
 * \file
 * \brief Définition de la classe GpioBoardTest.
 */

#ifndef ROBOTTEST_GPIOBOARDTEST_HPP
#define	ROBOTTEST_GPIOBOARDTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test de communication sur le board gpio DFDFR0013.
 */
class GpioBoardTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ArduinoTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::GpioBoardTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	GpioBoardTest()
			: pmx::ConsoleUnitTest("GpioBoardTest : ")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~GpioBoardTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}

#endif
