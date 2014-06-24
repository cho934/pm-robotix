/*!
 * \file
 * \brief Définition de la classe LedBarTest.
 */

#ifndef ROBOTTEST_LEDBARTEST_HPP
#define	ROBOTTEST_LEDBARTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test de clignotement des LEDs du tableau d'affichage par l'ActionManager.
 */
class LedBarTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref LedBarTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::LedBarTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	LedBarTest()
			: pmx::ConsoleUnitTest("LedBarTest : Blink Led board by ActionManager")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~LedBarTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
