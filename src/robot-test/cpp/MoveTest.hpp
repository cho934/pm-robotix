/*!
 * \file
 * \brief Définition de la classe MoveTest.
 */

#ifndef ROBOTTEST_MOVETEST_HPP
#define	ROBOTTEST_MOVETEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test d'avance.
 */
class MoveTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref MoveTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::MoveTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	MoveTest()
			: pmx::ConsoleUnitTest("MoveTest : Check encoder and forward move")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~MoveTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
