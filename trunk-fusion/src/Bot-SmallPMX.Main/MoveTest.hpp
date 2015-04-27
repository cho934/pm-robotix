/*!
 * \file
 * \brief Définition de la classe MotorTest.
 */

#ifndef MOVETEST_HPP_
#define	MOVETEST_HPP_

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test sur les codeurs moteur.
 */
class MoveTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref MotorTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("MoveTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	MoveTest() :
		FunctionalTest("MoveTest", "play with motors")
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

#endif
