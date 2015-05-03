

#ifndef DETECTIONTEST_HPP
#define	DETECTIONTEST_HPP

#include "../Common/FunctionalTest.hpp"
#include "../Log/LoggerFactory.hpp"

/*!
 * \brief Effectue un test sur les buttons.
 */
class DetectionTest: public FunctionalTest
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref DetectionTest.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("DetectionTest");
		return instance;
	}
public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	DetectionTest() :
		FunctionalTest("DetectionTest","detection adversaire")
	{
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~DetectionTest()
	{
	}

	/*!
	 * \brief Execute le test.
	 */
	virtual void run(int argc, char *argv[]);
};

#endif
