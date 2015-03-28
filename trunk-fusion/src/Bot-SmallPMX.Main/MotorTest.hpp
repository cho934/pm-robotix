/*!
 * \file
 * \brief Définition de la classe MotorTest.
 */

#ifndef MOTORTEST_HPP_
#define	MOTORTEST_HPP_

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test sur les codeurs moteur.
 */
class MotorTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref MotorTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("MotorTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	MotorTest() :
		FunctionalTest("MotorTest", "play with motors")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~MotorTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};

#endif
