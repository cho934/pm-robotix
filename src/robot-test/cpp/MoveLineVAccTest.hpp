/*!
 * \file
 * \brief Définition de la classe MoveLineVAccTest.
 */

#ifndef ROBOTTEST_MOVELINEVACCTEST_HPP
#define	ROBOTTEST_MOVELINEVACCTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test d'avance.
 */
class MoveLineVAccTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref MoveLineVAccTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::MoveLineVAccTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	MoveLineVAccTest()
			: pmx::ConsoleUnitTest("MoveLineVAccTest : ")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~MoveLineVAccTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
