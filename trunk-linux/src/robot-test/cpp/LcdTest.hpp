/*!
 * \file
 * \brief Définition de la classe LcdTest.
 */

#ifndef ROBOTTEST_LCDTEST_HPP
#define	ROBOTTEST_LCDTEST_HPP


#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

namespace robottest
{
/*!
 * \brief Effectue un test du LCD.
 */
class LcdTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref LcdTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::LcdTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	LcdTest()
			: pmx::ConsoleUnitTest("LcdTest : ")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~LcdTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
