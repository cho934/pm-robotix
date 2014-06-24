/*!
 * \file
 * \brief Définition de la classe Md25EncoderTest.
 */

#ifndef 	ROBOTTEST_MD25ENCODERTEST_HPP
#define	ROBOTTEST_MD25ENCODERTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test.
 */
class Md25EncoderTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref Md25EncoderTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::Md25EncoderTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	Md25EncoderTest()
			: pmx::ConsoleUnitTest("Md25EncoderTest : ")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~Md25EncoderTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
