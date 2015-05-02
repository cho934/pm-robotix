

#ifndef TIRETTETEST_HPP
#define	TIRETTETEST_HPP

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test sur la tirette.
 */
class TiretteTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref TiretteTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("TiretteTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	TiretteTest() :
		FunctionalTest("TiretteTest","test tirette")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~TiretteTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};

#endif
