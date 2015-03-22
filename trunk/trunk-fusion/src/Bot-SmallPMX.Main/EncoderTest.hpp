/*!
 * \file
 * \brief Définition de la classe EncoderTest.
 */

#ifndef ENCODERTEST_HPP_
#define	ENCODERTEST_HPP_

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test sur les codeurs moteur.
 */
class EncoderTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref EncoderTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("EncoderTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	EncoderTest() :
		FunctionalTest("EncoderTest", "Get values from encoders")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~EncoderTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};

#endif
