/*!
 * \file
 * \brief Définition de la classe ServoClampTest.
 */

#ifndef ROBOTTEST_SERVOCLAMPTEST_HPP
#define	ROBOTTEST_SERVOCLAMPTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test sur la clamp.
 */
class ServoClampTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoClampTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::ServoClampTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ServoClampTest()
			: pmx::ConsoleUnitTest("ServoClampTest : test clamp")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ServoClampTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
