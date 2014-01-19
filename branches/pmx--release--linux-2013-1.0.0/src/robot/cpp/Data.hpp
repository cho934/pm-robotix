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

        bool strategyCatchWithOpponent_;

        bool strategyPushGoldBar_;

    public:

        /*!
         * \brief Constructeur de la classe.
         */
        Data()
        {
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~Data()
        {
        }

        bool strategyCatchWithOpponent() const
        {
            return this->strategyCatchWithOpponent_;
        }
        void strategyCatchWithOpponent(bool value)
        {
            this->strategyCatchWithOpponent_ = value;
        }

        bool strategyPushGoldBar() const
        {
            return this->strategyPushGoldBar_;
        }
        void strategyPushGoldBar(bool value)
        {
            this->strategyPushGoldBar_ = value;
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
