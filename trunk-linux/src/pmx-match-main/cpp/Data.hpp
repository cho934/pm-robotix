/*!
 * \file
 * \brief Définition de la classe Data.
 */

#ifndef PMX_DATA_HPP
#define PMX_DATA_HPP

namespace pmx
{
/*!
 * \brief Represente les données partagées entre les différents états de l'automate.
 */
class Data
{
private:

	bool empty_;

	int useInternalEncoder_;

	int skipSetup_;

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	Data()
	{
		empty_ = 0;
		useInternalEncoder_ = 0;
		skipSetup_ = 0;
	}

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~Data()
	{
	}

	bool isEmpty() const
	{
		return this->empty_;
	}
	void isEmpty(bool empty)
	{
		this->empty_ = empty;
	}

	int useInternalEncoder() const
	{
		return this->useInternalEncoder_;
	}
	void useInternalEncoder(int useInternalEncoder)
	{
		this->useInternalEncoder_ = useInternalEncoder;
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
