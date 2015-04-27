/*!
 * \file
 * \brief Définition de la classe MotorTest.
 */

#ifndef SUPPORTTEST_HPP_
#define	SUPPORTTEST_HPP_

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test sur le mat motorisé.
 */
class SupportTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref SupportTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("SupportTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	SupportTest() :
		FunctionalTest("SupportTest", "test le mat")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~SupportTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};

#endif
