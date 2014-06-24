/* 
 * File:   DummyThread.hpp
 * Author: pmx
 *
 * Created on 12 avril 2013, 23:53
 */

#ifndef _DUMMYTHREAD_HPP
#define	_DUMMYTHREAD_HPP
/*!
 * \brief Classe implémentant un thread pour la réalisation des tests
 * unitaires.
 */
class DummyThread : public utils::Thread
{
private:

    /*!
     * \brief Retourne le \ref Logger associé à la classe \ref TestThread.
     */
    static const utils::Logger & logger()
    {
        static const utils::Logger & instance = utils::LoggerFactory::logger("test::DummyThread");
        return instance;
    }

    /*!
     * \brief Le nom de ce thread.
     */
    std::string name_;

protected:

    /*!
     * \brief Code exécuté par le thread de test lorsqu'il est actif.
     */
    virtual void execute()
    {
        if (this->name_ == "3td2")
        {
            sleep(5); //test du sleep sur le 2ème thread.
        }
        else
        {
            simpleCount(this->name_);
        }

    }

public:

    /*!
     * \brief fonction.
     */
    virtual void simpleCount(std::string)
    {
        //compter pendant 5s
        int j = 0;
        time_t start = time(NULL); //! \todo supprimer time_t et utiliser chronometer
        while (start + 5 > time(NULL))
        {
            j++;
        }

    }

    /*!
     * \brief Constructeur de la classe.
     * \param name
     *        Nom associé au thread créé.
     */
    DummyThread(const std::string & name) : name_(name)
    {
    }

    /*!
     * \brief Destructeur de la classe.
     */
    virtual inline ~DummyThread()
    {
        //   std::cout << "Thread destroy::"<< name_  << std::endl;
    }

    /*!
     * \return Nom du thread.
     */
    inline const std::string & name() const
    {
        return name_;
    }
};

#endif	/* _DUMMYTHREAD_HPP */



