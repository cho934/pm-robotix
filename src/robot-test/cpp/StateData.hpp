/*!
 * \file
 * \brief Définition de la classe StateData.
 */

#ifndef TEST_STATEDATA_HPP
#define TEST_STATEDATA_HPP

namespace pmx
{
    /*!
     * \brief Represente les données partagées entre les différents états de l'automate.
     */
    class StateData
    {
    private:

        bool empty_;

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        StateData()
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~StateData()
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
    };
}

#endif
