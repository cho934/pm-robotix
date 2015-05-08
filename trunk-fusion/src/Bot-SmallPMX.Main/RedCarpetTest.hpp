/*!
 * \file
 * \brief Définition de la classe RedCarpetTest.
 */

#ifndef REDCARPETTEST_HPP_
#define	REDCARPETTEST_HPP_

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test sur les servomoteurs standards.
 */
class RedCarpetTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("RedCarpetTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	RedCarpetTest() :
		FunctionalTest("RedCarpetTest", "test servomotors et tapis rouge")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~RedCarpetTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};

#endif
