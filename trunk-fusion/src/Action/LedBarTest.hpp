/*!
 * \file
 * \brief Définition de la classe LedBarTest.
 */

#ifndef LEDBARTEST_HPP
#define	LEDBARTEST_HPP

#include "../Common/ConsoleUnitTest.hpp"
//#include "../../common/cpp/LoggerFactory.hpp"

/*!
 * \brief Effectue un test de clignotement des LEDs du tableau d'affichage.
 */
class LedBarTest: public ConsoleUnitTest
{
private:

	/*!
	 * \brief //TODO Retourne le \ref Logger associé à la classe \ref LedIndicatorTest.
	 */
	//static inline const utils::Logger & logger()
	//{
	//	static const utils::Logger & instance = utils::LoggerFactory::logger("LedBarTest");
	//	return instance;
	//}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	LedBarTest() :
			ConsoleUnitTest("LedBarTest : Blink Led board directly")
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

#endif
