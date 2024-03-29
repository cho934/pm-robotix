/*!
 * \file
 * \brief Définition de la classe Data.
 */

#ifndef PMX_DATA_HPP
#define PMX_DATA_HPP

#include "StateIADecisionMaker.hpp"

namespace pmx
{
/*!
 * \brief Represente les données partagées entre les différents états de l'automate.
 */
class Data
{
private:

	bool empty_;

	int useExternalEncoder_;

	int skipSetup_;

	bool end90s_;


public:

	pmx::StateIADecisionMaker* decisionMaker;

	/*!
	 * \brief Constructeur de la classe.
	 */
	Data()
	{
		decisionMaker = new pmx::StateIADecisionMaker();
		empty_ = 0;
		useExternalEncoder_ = 0;
		skipSetup_ = 0;
		end90s_ = 0;
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~Data()
	{
	}

	bool end90s() const
	{
		return this->end90s_;
	}
	void end90s(bool end)
	{
		this->end90s_ = end;
	}

	bool isEmpty() const
	{
		return this->empty_;
	}
	void isEmpty(bool empty)
	{
		this->empty_ = empty;
	}

	int useExternalEncoder() const
	{
		return this->useExternalEncoder_;
	}
	void useExternalEncoder(int useEncoder)
	{
		this->useExternalEncoder_ = useEncoder;
	}

	int skipSetup() const
	{
		return this->skipSetup_;
	}
	void skipSetup(int skip)
	{
		this->skipSetup_ = skip;
	}
};
}

#endif
