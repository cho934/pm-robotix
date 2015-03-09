/*!
 * \file
 * \brief Class definition for functional tests.
 */

#ifndef COMMON_FUNCTIONALTEST_HPP_
#define	COMMON_FUNCTIONALTEST_HPP_

#include <string>

/*!
 * \brief Abstract class to implement functional tests using ConsoleManager.
 */
class FunctionalTest
{
private:

	/*!
	 * \brief Nom du test.
	 */
	std::string name_;

protected:

	/*!
	 * \brief Constructeur de la classe.
	 * \param name
	 *        Nom du test.
	 */
	FunctionalTest(const std::string & name) :
			name_(name)
	{
	}

public:

	/*!
	 * Destructeur de la classe.
	 */
	virtual inline ~ FunctionalTest()
	{
	}

	/*!
	 * \return Nom du test.
	 */
	inline const std::string & name() const
	{
		return name_;
	}

	/*!
	 * Méthode exécutant le test associé.
	 */
	virtual void run(int argc, char *argv[]) =0;
};

#endif
