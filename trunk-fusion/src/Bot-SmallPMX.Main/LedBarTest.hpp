/*!
 * \file
 * \brief Définition de la classe LedBarTest.
 */

#ifndef LEDBARTEST_HPP
#define	LEDBARTEST_HPP

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test de clignotement des LEDs du tableau d'affichage.
 */
class LedBarTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref LedBarTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("LedBarTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	LedBarTest() :
		FunctionalTest("LedBarTest","Blink Leds")
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
