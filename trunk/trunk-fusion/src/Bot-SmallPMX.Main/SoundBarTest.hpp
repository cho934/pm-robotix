/*!
 * \file
 * \brief Définition de la classe SoundBarTest.
 */

#ifndef SOUNDBARTEST_HPP_
#define	SOUNDBARTEST_HPP_

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test de clignotement de haut parleur.
 */
class SoundBarTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref SoundBarTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("SoundBarTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	SoundBarTest() :
		FunctionalTest("SoundTest", "Play sounds")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~SoundBarTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};

#endif
