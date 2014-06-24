/*!
 * \file
 * \brief Définition de la classe ExtEncoderTest.
 */

#ifndef 	ROBOTTEST_EXTENCODERTEST_HPP
#define	ROBOTTEST_EXTENCODERTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test.
 */
class ExtEncoderTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ExtEncoderTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::ExtEncoderTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ExtEncoderTest()
			: pmx::ConsoleUnitTest("ExtEncoderTest : ")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ExtEncoderTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
