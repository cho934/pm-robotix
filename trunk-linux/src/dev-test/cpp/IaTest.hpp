/*!
 * \file
 * \brief Définition de la classe IaTest.
 */

#ifndef TEST_IATEST_H
#define	TEST_IATEST_H

#include "../../common/cpp/LoggerFactory.hpp"
#include "DevUnitTest.hpp"
#include "../../common/c/ia.h"

namespace test
{
/*!
 * \brief Teste la classe IaTest.
 */
class IaTest: public utils::DevUnitTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref PidTest.
	 */
	static const utils::Logger & logger()
	{
		static const utils::Logger & instance = utils::LoggerFactory::logger("test::IaTest");
		return instance;
	}

public:

	/*!
	 * \brief Constructeur par défaut.
	 */
	IaTest() : utils::DevUnitTest("IaTest")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual inline ~IaTest()
	{
	}

	/*!
	 * \brief Execute les tests associés à la classe \ref PidTest.
	 */
	virtual void suite();

	/*!
	 * \brief Test des getters de la classe \ref utils::PID.
	 */
	void testcho();
};
}

#endif
