/*!
 * \file
 * \brief Définition de la classe OdometryPositionManager.
 */

#ifndef PMX_ODOMETRYPOSITIONMANAGER_HPP
#define	PMX_ODOMETRYPOSITIONMANAGER_HPP

#include "PositionManager.hpp"
#include "LoggerFactory.hpp"
#include "SvgWriter.hpp"
#include "ActionManager.hpp"
#include "IAction.hpp"
#include "ARobotElement.hpp"

namespace pmx
{
    
    /*!
     * \brief Enumération des types d'encodeur.
     */
    enum EncoderType
    { ENCODERFREE, ENCODERMOTOR };

    /*!
     * \brief Cette classe permet de gérer le positionnement du robot via les codeurs.
     */
    class OdometryPositionManager : public pmx::PositionManager, public ARobotElement
    {
    private:
        
        /*!
         * \brief Retourne le \ref Logger nommé csv associé à la classe \ref OdometryPositionManager.
         */
        static inline const utils::Logger & csv()
        {
            static const utils::Logger & csv_ = utils::LoggerFactory::logger("pmx::OdometryPositionManager::csv");
            return csv_;
        }
        
        /*!
         * \brief Nombre absolu d'impulsion depuis le dernier traitement.
         * \sa ::compute()
         */
        int count_;
        int countOld_;
        
        /*!
         * \brief Nombre d'impulsion sur l'encodeur gauche depuis le dernier traitement.
         */
        int countLeft_;
        int countLeftOld_;
        
        /*!
         * \brief Nombre d'impulsion sur l'encodeur droit depuis le dernier traitement.
         */
        int countRight_;
        int countRightOld_;

        /*!
         * \brief Type d'encoder à utiliser pour l'odométrie.
         */
        EncoderType encoderUse_;

        /*!
         * \brief Fréquence de calcul d'odométrie.
         */
        int freqOdo_;

        /*!
         * \brief longueur initial d'un moveD du vecteur d'arrivée.
         */
        double vdInit_;

    public:

        /*!
         * \brief Constructeur par défaut.
         */
        OdometryPositionManager(pmx::Robot & robot, EncoderType encoder);
        
        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~ OdometryPositionManager()
        {}
        
        virtual void onLeftPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer chrono);
        
        virtual void onRightPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer chrono);        
        
        /*!
         * \brief Update the current position of the robot.
         */
        void compute(utils::SvgPositionColor color, bool force);

        /*!
         * \brief Change la fréquence de calcul de l'odométrie.
         */
        void changeFrequency(int freq)
        {
            freqOdo_=freq;
        }
        /*!
         * \brief Ajouter une action
         */
        void addAction();

        /*!
         * \brief Reset les valeurs de cette classe.
         */
        void reset();

        /*!
         * \brief Accesseur du vd Initial d'un moveD.
         */
        inline void vdInit(double value)
        {
            vdInit_=value;
        }

        inline double vdInit() const
        {
            return vdInit_;
        }
    };

    /*!
     * \brief Cette action permet de definir les actions effectuées par l'odométrie.
     *
     */
    class OdometryAction : public IAction
    {
    private:

        /*!
         * \brief Retourne le \ref Logger associé à la classe \ref ClampAction.
         */
        static const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("pmx::OdometryAction");
            return instance;
        }

        /*!
         * \brief Référence vers la pince associé.
         */
        OdometryPositionManager & odometryPositionManager_;

        /*!
         * \brief libellé de l'action à exécuter.
         */
        int action_;

        /*!
         * \brief chronomètre de la pince permettant de définir le temps d'ouverture/fermeture.
         */
        utils::Chronometer chrono_;

        /*!
         * \brief dernier temps issu du chronometre.
         */
        long lastTime_;

        


    public:

        /*!
         * \brief Constructeur de la classe.
         * \param positionManager
         *        Reference vers le positionManager.
         */
        OdometryAction(OdometryPositionManager & odometryPositionManager_, int action);

        /*!
         * \brief Destructeur de la classe.
         */
        virtual inline ~OdometryAction()
        {}

        virtual bool execute(IRobotOut * out);

        virtual inline std::string info()
        {
            return "OdometryAction";
        }

        double round(double number)
        {
            return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
        }
    };
}

#endif
