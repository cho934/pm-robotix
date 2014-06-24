/*!
 * \file
 * \brief Définition de la classe FindPIDDTest.
 */

#ifndef ROBOTTEST_FINDPIDDTEST_HPP
#define	ROBOTTEST_FINDPIDDTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test d'asservissement AlphaDelta afin avec des coeff PID.
 */
class FindPIDDTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref FindPIDTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::FindPIDDTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	FindPIDDTest()
			: pmx::ConsoleUnitTest("FindPIDDTest : Test les parametres PID sur une ligne")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~FindPIDDTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
