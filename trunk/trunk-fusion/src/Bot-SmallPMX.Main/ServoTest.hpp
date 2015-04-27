/*!
 * \file
 * \brief Définition de la classe ServoTest.
 */

#ifndef SERVOTEST_HPP_
#define	SERVOTEST_HPP_

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test sur les servomoteurs standards.
 */
class ServoTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ServoTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("ServoTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ServoTest() :
		FunctionalTest("ServoTest", "test servomotors")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~ServoTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};

#endif
