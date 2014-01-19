/*!
 * \file
 * \brief Implémentation de la classe SensorManager.
 */

/*! \todo Check if extern is required - not used in other files */
extern "C"
{
#include <native/task.h>
#include <native/intr.h>
#include <as_devices/as_gpio.h>
}

#include <iostream>
#include <sys/mman.h>
#include <cstdio>
#include "SensorManager.hpp"
#include "RobotInOutFactory.hpp"
#include "MotorWay.hpp"
#include "LedIndicator.hpp"
#include "Md25.hpp"

#define TASK_PRIO 99 /* Highest RT priority */
#define TASK_MODE 0 /* No flags */
#define TASK_STKSZ 0 /* Stack size (use default one) */

long s_countLeft;
long s_countRight;

long s_countLeftOld;
long s_countRightOld;

long countLeftMd25;
long countRightMd25;

long countLeftMd25Old;
long countRightMd25Old;

int s_pinDephL = 0, s_pinDephR = 0;

int s_error_intr = 0;

RT_INTR s_intr_left;
RT_INTR s_intr_right;

RT_TASK s_server_left;
RT_TASK s_server_right;

RT_INTR s_intr_R_deph_rising;
RT_INTR s_intr_R_deph_falling;
RT_INTR s_intr_L_deph_rising;
RT_INTR s_intr_L_deph_falling;

RT_TASK s_server_R_deph_rising;
RT_TASK s_server_R_deph_falling;
RT_TASK s_server_L_deph_rising;
RT_TASK s_server_L_deph_falling;

const utils::Logger & logger = utils::LoggerFactory::logger("pmx::SensorManager");

extern "C"
{

    void s_task_left(void*)
    {
        if (0 != rt_intr_enable(&s_intr_left))
        {
            logger.error("Error : enabling left rt_intr_enable()");
            s_error_intr = 1;
        }
        else
        {
            while (true)
            {
                int err = rt_intr_wait(&s_intr_left, TM_INFINITE);
                if (err >= 0)
                {
                    //detection dephasage
                    if (s_pinDephL == 1)
                    {
                        s_countLeft++;
                    }
                    else
                    {
                        s_countLeft--;
                    }
                }
                else
                {
                    break; //break si intr en cours de delete.
                }
            }
        }
    }

    void s_task_right(void*)
    {
        if (0 != rt_intr_enable(&s_intr_right))
        {
            logger.error("Error : enabling right rt_intr_enable()");
            s_error_intr = 2;
        }
        else
        {
            while (true)
            {
                int err = rt_intr_wait(&s_intr_right, TM_INFINITE);
                if (err >= 0)
                {
                    //detection dephasage
                    if (s_pinDephR == 0)
                    {
                        s_countRight++;
                    }
                    else
                    {
                        s_countRight--;
                    }
                }
                else
                {
                    break; //break si interruption en cours de suppression.
                }
            }
        }
    }

    void s_task_L_deph_falling(void*)
    {
        if (0 != rt_intr_enable(&s_intr_L_deph_falling))
        {
            logger.error("Error : enabling left deph falling");
            s_error_intr = 3;
        }
        else
        {
            //printf("s_task_L_deph_falling:ok\n");
            while (true)
            {
                int err = rt_intr_wait(&s_intr_L_deph_falling, TM_INFINITE);
                if (err >= 0)
                {
                    s_pinDephL = 0;
                }
                else
                {
                    break; //break si intr en cours de delete.
                }
            }
        }
    }

    void s_task_L_deph_rising(void*)
    {
        if (0 != rt_intr_enable(&s_intr_L_deph_rising))
        {
            logger.error("Error : enabling right deph rising");
            s_error_intr = 4;
        }
        else
        {
            while (true)
            {
                int err = rt_intr_wait(&s_intr_L_deph_rising, TM_INFINITE);
                if (err >= 0)
                {
                    s_pinDephL = 1;
                }
                else
                {
                    break; //break si intr en cours de delete.
                }
            }
        }
    }

    void s_task_R_deph_falling(void*)
    {
        if (0 != rt_intr_enable(&s_intr_R_deph_falling))
        {
            logger.error("Error : enabling right deph falling");
            s_error_intr = 5;
        }
        else
        {
            while (true)
            {
                int err = rt_intr_wait(&s_intr_R_deph_falling, TM_INFINITE);
                if (err >= 0)
                {
                    s_pinDephR = 0;
                }
                else
                {
                    break; //break si intr en cours de delete.
                }
            }
        }
    }

    void s_task_R_deph_rising(void*)
    {
        if (0 != rt_intr_enable(&s_intr_R_deph_rising))
        {
            logger.error("Error : enabling right deph rising");
            s_error_intr = 6;
        }
        else
        {
            while (true)
            {
                int err = rt_intr_wait(&s_intr_R_deph_rising, TM_INFINITE);
                if (err >= 0)
                {
                    s_pinDephR = 1;
                }
                else
                {
                    break; //break si intr en cours de delete.
                }
            }
        }
    }
}

pmx::SensorManager::SensorManager() : stop_(false), firePulseEnabled_(true)
{
}

/*!
 * \brief indique le nombre d'impulsion du codeur gauche.
 * \param value
 *          nombre d'impulsions du codeur gauche (prenant déjà en compte le sens de rotation.
 * \param chonometre de temps écoulé.
 *          Temps écoulé en us depuis le start du sensorManager.
 * \param way
 *          Le sens de rotation de la dernière impulsion.
 */
void
pmx::SensorManager::fireLeftPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer chrono)
{
    /*if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "fireLeftPulse() [value:" << value << "] [time:" << chrono.getElapsedTimeInMicroSec() << "]" << utils::end;
    }*/
    lock();
    utils::PointerList <IEncoderListener*>::iterator i = this->encoderListeners_.begin();
    while (i != encoderListeners_.end())
    {
        IEncoderListener* listener = *i;
        listener->onLeftPulse(motorEncoderValue, freeEncoderValue, chrono);
        i++;
    }
    unlock();
}

void
pmx::SensorManager::fireRightPulse(int motorEncoderValue, int freeEncoderValue, utils::Chronometer chrono)
{
    /*if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "fireRightPulse() [value:" << value << "] [time:" << chrono.getElapsedTimeInMicroSec() << "]" << utils::end;
    }*/
    lock();
    utils::PointerList <IEncoderListener*>::iterator i = this->encoderListeners_.begin();
    while (i != encoderListeners_.end())
    {
        IEncoderListener* listener = *i;
        listener->onRightPulse(motorEncoderValue, freeEncoderValue, chrono);
        i++;
    }
    unlock();
}

void
pmx::SensorManager::execute()
{
    debugThread("SensorManager");
    this->executeWithNoBlockingRead();
}

void
pmx::SensorManager::executeWithNoBlockingRead()
{
    lock();
    logger().debug() << "executeWithNoBlockingRead : SensorManager is started with "
            << this->encoderListeners_.size() << " + "
            << this->sensorListeners_.size() << " listener(s)"
            << utils::end;
    unlock();
    pmx::IRobotIn * robotIn = pmx::RobotInOutFactory::instance()->robotIn();

    //Configuration des IRQs (pb avec uniquement le load du fichier !!)
    struct as_gpio_device *pd25, *pd26, *pd19, *pd24, *pd30, *pd29;
    pd25 = as_gpio_open('D', 25); //IMPGD (rising interrupt)
    pd29 = as_gpio_open('D', 29); //IMPDD doublon (falling interrupt)
    pd26 = as_gpio_open('D', 26); //IMPDD (rising interrupt)
    pd30 = as_gpio_open('D', 30); //IMPGD doublon (falling interrupt)
    pd24 = as_gpio_open('D', 24); //IMPG
    pd19 = as_gpio_open('D', 19); //IMPD
    //mode IRQ des entrées:
    as_gpio_set_irq_mode(pd19, GPIO_IRQ_MODE_RISING);
    as_gpio_set_irq_mode(pd24, GPIO_IRQ_MODE_RISING);
    as_gpio_set_irq_mode(pd26, GPIO_IRQ_MODE_RISING);
    as_gpio_set_irq_mode(pd30, GPIO_IRQ_MODE_FALLING);
    as_gpio_set_irq_mode(pd25, GPIO_IRQ_MODE_RISING);
    as_gpio_set_irq_mode(pd29, GPIO_IRQ_MODE_FALLING);


    /* Cause all currently mapped pages of the process to be memory resident
   until unlocked by a call to the `munlockall', until the process exits,
   or until the process calls `execve'.  */
    mlockall(MCL_CURRENT | MCL_FUTURE);


    //affichage LEDINDICATOR
    pmx::LedIndicator::instance().setOff(4);
    //init des varibles d'erreur de lancement de tâches matérielles:
    int s_task_error = 0;

    //creation des IRQs
    //70=>PA6 ; 179=>PD19; 184=>PD24 ; 185=>PD25 ; 186=>PD26 ; 189=>PD29 ; 190=>PD30
    if (0 != rt_intr_create(&s_intr_left, "IrqLeft", 184, 0))
    {
        //printf("rt_intr_create : error for left\n");
        logger().error() << "rt_intr_create : error for left" << utils::end;
        s_task_error = 1;
    }
    else if (0 != rt_intr_create(&s_intr_right, "IrqRight", 179, 0))
    {
        //printf("rt_intr_create : error for right\n");
        logger().error() << "rt_intr_create : error for right" << utils::end;
        s_task_error = 2;
    }
    else if (0 != rt_intr_create(&s_intr_R_deph_rising, "IrqRightDephRising", 186, 0))
    {
        //printf("rt_intr_create : error for right deph rising\n");
        logger().error() << "rt_intr_create : error for right deph rising" << utils::end;
        s_task_error = 3;
    }
    else if (0 != rt_intr_create(&s_intr_R_deph_falling, "IrqRightDephFalling", 190, 0))
    {
        //printf("rt_intr_create : error for right deph falling\n");
        logger().error() << "rt_intr_create : error for right deph falling" << utils::end;
        s_task_error = 4;
    }
    else if (0 != rt_intr_create(&s_intr_L_deph_rising, "IrqLeftDephRising", 185, 0))
    {
        //printf("rt_intr_create : error for left deph rising\n");
        logger().error() << "rt_intr_create : error for left deph rising" << utils::end;
        s_task_error = 5;
    }
    else if (0 != rt_intr_create(&s_intr_L_deph_falling, "IrqLeftDephFalling", 189, 0))
    {
        //printf("rt_intr_create : error for left deph falling\n");
        logger().error() << "rt_intr_create : error for left deph falling" << utils::end;
        s_task_error = 6;
    }
    else if (0 != rt_task_create(&s_server_left, "IrqServerLeft", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for left\n");
        logger().error() << "rt_task_start : error for left" << utils::end;
        s_task_error = 7;
    }
    else if (0 != rt_task_create(&s_server_right, "IrqServerRight", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for right\n");
        logger().error() << "rt_task_start : error for right" << utils::end;
        s_task_error = 8;
    }
    else if (0 != rt_task_create(&s_server_R_deph_rising, "IrqServerRightDephRising", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for right deph rising\n");
        logger().error() << "rt_task_start : error for right deph rising" << utils::end;
        s_task_error = 9;
    }
    else if (0 != rt_task_create(&s_server_R_deph_falling, "IrqServerRightDephFalling", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for right deph falling\n");
        logger().error() << "rt_task_start : error for right deph falling" << utils::end;
        s_task_error = 10;
    }
    else if (0 != rt_task_create(&s_server_L_deph_rising, "IrqServerLeftDephRising", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for left deph rising\n");
        logger().error() << "rt_task_start : error for left deph rising" << utils::end;
        s_task_error = 11;
    }
    else if (0 != rt_task_create(&s_server_L_deph_falling, "IrqServerLeftDephFalling", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for left deph falling\n");
        logger().error() << "rt_task_start : error for left deph falling" << utils::end;
        s_task_error = 12;
    }
    else
    {
        rt_task_start(&s_server_left, &s_task_left, NULL);
        rt_task_start(&s_server_right, &s_task_right, NULL);
        rt_task_start(&s_server_R_deph_rising, &s_task_R_deph_rising, NULL);
        rt_task_start(&s_server_R_deph_falling, &s_task_R_deph_falling, NULL);
        rt_task_start(&s_server_L_deph_rising, &s_task_L_deph_rising, NULL);
        rt_task_start(&s_server_L_deph_falling, &s_task_L_deph_falling, NULL);

        //affichage LEDINDICATOR
        if (s_task_error == 0)
        {
            pmx::LedIndicator::instance().setOn(4); //ok
        }
        else
        {
            pmx::LedIndicator::instance().setOff(4); //nok
        }

        //test erreur intr
        if (s_error_intr != 0)
        {
            pmx::LedIndicator::instance().setOff(4); //nok
        }
        int nb;

        countLeftMd25Old = utils::Md25::instance().ensureGetEncoder(countLeftMd25Old, MD25_ENCODER1_REG);
        countRightMd25Old = utils::Md25::instance().ensureGetEncoder(countRightMd25Old, MD25_ENCODER2_REG);

        while (!stop_)
        {
            if (firePulseEnabled_)
            {
                countLeftMd25 = utils::Md25::instance().ensureGetEncoder(countLeftMd25, MD25_ENCODER1_REG);
                long deltaLeftMd25 = countLeftMd25 - countLeftMd25Old;
                long s_countLeftTemp = s_countLeft;
                long delta_s_countLeft = s_countLeftTemp - s_countLeftOld;
                //traitement des codeurs gauche 
                if (delta_s_countLeft != 0 || deltaLeftMd25 != 0) //lance un fire uniquement s'il y a eu une impulsion.
                {
                    fireLeftPulse(deltaLeftMd25, delta_s_countLeft, chrono_);
                }
                countLeftMd25Old = countLeftMd25;
                s_countLeftOld = s_countLeftTemp;

                countRightMd25 = utils::Md25::instance().ensureGetEncoder(countRightMd25, MD25_ENCODER2_REG);
                long deltaRightMd25 = countRightMd25 - countRightMd25Old;
                long s_countRightTemp = s_countRight;
                long delta_s_countRight = s_countRightTemp - s_countRightOld;
                if (delta_s_countRight != 0 || deltaRightMd25 != 0)
                {
                    fireRightPulse(deltaRightMd25, delta_s_countRight, chrono_);
                }
                countRightMd25Old = countRightMd25;
                s_countRightOld = s_countRightTemp;
            }

            logger().debug() << " while (!stop_)" << utils::end;
            
            this->lock();
            // Traitement des autres capteurs
            if (sensorListeners_.size() > 0)
            {
                if (logger().isActive(utils::Level::DEBUG))
                {
                    if (nb != (int) sensorListeners_.size())//si changement de nombre
                    {
                        logger().debug() << "Number of ISensorListener : " << sensorListeners_.size() << utils::end;
                        nb = sensorListeners_.size();
                    }
                }
               
                ISensorListener * listener = sensorListeners_.front();
                sensorListeners_.pop_front();


                this->unlock();
                bool persist = listener->execute(robotIn);
                this->lock();
                if (persist)
                {
                    sensorListeners_.push_back(listener);
                }

            }
            this->unlock();
            usleep(3000); //pour laisser la main si besoin
        } //fin while
    }
    // Suppression des taches
    rt_intr_delete(&s_intr_left);
    rt_intr_delete(&s_intr_right);

    rt_task_delete(&s_server_left);
    rt_task_delete(&s_server_right);

    rt_intr_delete(&s_intr_R_deph_rising);
    rt_intr_delete(&s_intr_R_deph_falling);
    rt_intr_delete(&s_intr_L_deph_rising);
    rt_intr_delete(&s_intr_L_deph_falling);

    rt_task_delete(&s_server_R_deph_rising);
    rt_task_delete(&s_server_R_deph_falling);
    rt_task_delete(&s_server_L_deph_rising);
    rt_task_delete(&s_server_L_deph_falling);

    this->lock();
    // Suppression des listeners
    if (sensorListeners_.size() > 0)
    {
        if (logger().isActive(utils::Level::DEBUG))
        {
            logger().debug() << "Number of end ISensorListener : " << sensorListeners_.size() << utils::end;
        }
        utils::PointerList <ISensorListener *>::iterator i = sensorListeners_.begin();
        while (i != sensorListeners_.end())
        {
            ISensorListener * listener = *i;
            listener->execute(robotIn);

            utils::PointerList <ISensorListener *>::iterator old = i;
            i++;

            delete listener;
            this->sensorListeners_.erase(old);
        }
    }
    this->unlock();
    logger().info("SensorManager is stopped");
}

