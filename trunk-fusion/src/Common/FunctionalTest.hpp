/*!
 * \file
 * \brief Définition de la classe Functional test.
 */

#ifndef FUNCTIONALTEST_HPP
#define	FUNCTIONALTEST_HPP

#include <string>

/*!
 * \brief Classe abstraite servant de base pour les tests de fonctionnement
 * du robot.
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
