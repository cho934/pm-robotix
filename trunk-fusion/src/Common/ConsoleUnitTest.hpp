/*!
 * \file
 * \brief Définition de la classe ConsoleUnitTest.
 */

#ifndef CONSOLEUNITTEST_HPP
#define	CONSOLEUNITTEST_HPP

#include <string>

/*!
 * \brief Classe abstraite servant de base pour les tests de fonctionnement
 * du robot.
 */
class ConsoleUnitTest
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
	ConsoleUnitTest(const std::string & name) :
			name_(name)
	{
	}

public:

	/*!
	 * Destructeur de la classe.
	 */
	virtual inline ~ ConsoleUnitTest()
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
