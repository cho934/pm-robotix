/*!
 * \file
 * \brief Définition de la classe LedBarTest.
 */

#ifndef BUTTONBARTEST_HPP
#define	BUTTONBARTEST_HPP

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test sur les buttons.
 */
class ButtonBarTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ButtonBarTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("ButtonBarTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ButtonBarTest() :
		FunctionalTest("ButtonBarTest","Button test")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ButtonBarTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};

#endif
