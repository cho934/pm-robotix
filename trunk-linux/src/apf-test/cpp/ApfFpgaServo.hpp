/*!
 * \file
 * \brief Définition de la classe ApfFpgaServo.
 */

#ifndef TEST_APFFPGASERVO_HPP
#define TEST_APFFPGASERVO_HPP

#include "../../common/cpp/ConsoleUnitTest.hpp"
#include "../../common/cpp/LoggerFactory.hpp"
#include "../../common/cpp/Mutex.hpp"

#define SERVO_DRIVER_SYSFS_BASE "/sys/class/servo/"
#define SERVO_DRIVER_SERVO_FILE "servo"
#define SERVO_DRIVER_SERVO_POSITION_FILE "desired_position"
#define SERVO_DRIVER_SERVO_ENABLE_FILE "enable"
#define SERVO_DRIVER_SERVO_OFFSET_FILE "offset"
#define SERVO_DRIVER_SERVO_MIN_FILE "lower_boundary"
#define SERVO_DRIVER_SERVO_MAX_FILE "upper_boundary"
#define SERVO_DRIVER_SERVO_CURRENT_POS "current_position"
#define NbMaxServo 32

namespace test
{
    /*!
     * \brief Effectue un test utilisant le FPGA pour contôler les servomoteurs.
     */
    class ApfFpgaServo : public pmx::ConsoleUnitTest, utils::Mutex
    {
    private:

    	/*!
         * \brief Retourne le \ref Logger associé à la classe \ref ApfOutDacTest.
         */
        static inline const utils::Logger & logger()
        {
            static const utils::Logger & instance = utils::LoggerFactory::logger("test::ApfFpgaServo");
            return instance;
        }

        int *servoEnableBuffer;

		int *servoMinBuffer;

		int *servoMaxBuffer;

		int *servoOffsetBuffer;

		int *servoPositionBuffer;



    public:

        /*!
         * \brief Constructeur de la classe.
         */
        ApfFpgaServo() : pmx::ConsoleUnitTest("ApfFpgaServo : Test FPGA to control servomotor")
        {
        	servoEnableBuffer = new int[NbMaxServo];
			servoMinBuffer = new int[NbMaxServo];
			servoMaxBuffer = new int[NbMaxServo];
			servoOffsetBuffer = new int[NbMaxServo];
			servoPositionBuffer = new int[NbMaxServo];
			for (int i = 0; i < NbMaxServo; i++)
			{
				servoEnableBuffer[i] = 0;
				servoMinBuffer[i] = 0;
				servoMaxBuffer[i] = 0;
				servoOffsetBuffer[i] = 0;
				servoPositionBuffer[i] = 0;
			}
        }

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~ApfFpgaServo()
        {
        }
        
        /*!
         * \brief Execute le test.
         */
        virtual void run(int argc, char *argv[]);


        /*!
		 * \brief Permet d'activer un servomoteur ou non (freewheeling).
		 * \param servoID : identifiant du servomoteur.
		 * \param value : prend la valeur 0 ou 1.
		 */
		virtual void setServoEnable(int servoID, int value);

		/*!
		 * \brief Mets à jour la valeur d'offset du servo associé.
		 */
		virtual void setServoOffset(int, int);

		/*!
		 * \brief Tourne le servo à la valeur de position demandée.
		 */
		virtual void setServoPosition(int, int);

		/*!
		 * \brief indique l'identifiant du servomoteur.
		 */
		virtual int getServoId(int servoID);

		/*!
		 * \brief indique la valeur courante de la position du servo.
		 */
		virtual int getServoCurrentPosition(int servoID);
    };
};

#endif
