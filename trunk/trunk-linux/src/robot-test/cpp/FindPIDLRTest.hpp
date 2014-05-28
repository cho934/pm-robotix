/*!
 * \file
 * \brief Définition de la classe FindPIDLRTest.
 */

#ifndef ROBOTTEST_FINDPIDLRTEST_HPP
#define	ROBOTTEST_FINDPIDLRTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test afin avec des coeff PID.
 */
class FindPIDLRTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref FindPIDLRTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::FindPIDLRTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	FindPIDLRTest()
			: pmx::ConsoleUnitTest("FindPIDLRTest : Permet de tester les parametres PID L et R")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~FindPIDLRTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
