#ifndef ASSERV_HPP_
#define ASSERV_HPP_

#include "../LogAppender/LoggerFactory.hpp"


class Asserv
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref Asserv.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("Asserv");
		return instance;
	}


public:

	/*!
	 * \brief Constructor.
	 */
	Asserv()
	{
	}

	/*!
	 * \brief Destructor.
	 */
	~Asserv()
	{
	}

	/*!
	 * \brief Active les actions.
	 *
	 * Cette méthode lance le thread gérant le ActionManager.
	 */
	void start();

	/*!
	 * \brief Arrete le robot et libère les ressources associés.
	 */
	void stop();

};

#endif
