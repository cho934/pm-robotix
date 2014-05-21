/*!
 * \file
 * \brief Définition de la classe FindPIDADTest.
 */

#ifndef ROBOTTEST_FINDPIDLINETEST_HPP
#define	ROBOTTEST_FINDPIDLINETEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test d'asservissement AlphaDelta afin avec des coeff PID.
 */
class FindPIDADTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref FindPIDTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::FindPIDADTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	FindPIDADTest()
			: pmx::ConsoleUnitTest("FindPIDADTest : ")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~FindPIDADTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
