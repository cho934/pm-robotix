/*!
 * \file
 * \brief Définition de la classe IrSensorsGroupTest.
 */

#ifndef ROBOTTEST_IRSENSORSGROUPTEST_HPP
#define	ROBOTTEST_IRSENSORSGROUPTEST_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"

namespace robottest
{
/*!
 * \brief Effectue un test de détection par IR.
 */
class IrSensorsGroupTest: public pmx::ConsoleUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref IrSensorsGroupTest.
	 */
	static inline const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("robottest::IrSensorsGroupTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	IrSensorsGroupTest()
			: pmx::ConsoleUnitTest("IrSensorsGroupTest : Test de détection IR")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~IrSensorsGroupTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};
}


#endif
