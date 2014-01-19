/*!
 * \file
 * \brief Implémentation de la classe SensorManager.
 */

extern "C"
{
#include <native/task.h>
#include <native/intr.h>
#include <as_devices/as_gpio.h>
}
#include <iostream>
#include "SensorManager.hpp"
#include "RobotInOutFactory.hpp"
#include "MotorWay.hpp"
#include "LedIndicator.hpp"

#define TASK_PRIO 99 /* Highest RT priority */
#define TASK_MODE 0 /* No flags */
#define TASK_STKSZ 0 /* Stack size (use default one) */

int s_countLeft;
int s_countRight;
int s_pinDephL = 0, s_pinDephR = 0;
pmx::MotorWay s_wayLeft, s_wayRight;

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

extern "C"
{

    void s_task_left(void*)
    {
        //printf("execute task_left\n");
        if (0 != rt_intr_enable(&s_intr_left))
        {
            printf("Error : enabling left rt_intr_enable()\n");
            s_error_intr = 1;
        }else
        {
            //ouverture pin de dephasage gauche IMPGD
            //s_pd25 = as_gpio_open('D', 25); //IMPGD

            while (true)
            {
                int err = rt_intr_wait(&s_intr_left, TM_INFINITE);
                if (err >= 0)
                {
                    //detection dephasage
                    //printf("DephG %d \n", s_pinDephL);
                    if (s_pinDephL == 1)
                    {
                        s_countLeft++;
                        s_wayLeft = pmx::FORWARD;
                    }else
                    {
                        s_countLeft--;
                        s_wayLeft = pmx::BACK;
                    }
                }else
                {
                    break; //break si intr en cours de delete.
                }
            }
        }
    }

    void s_task_right(void*)
    {
        //printf("execute task_right\n");
        if (0 != rt_intr_enable(&s_intr_right))
        {
            printf("Error : enabling right rt_intr_enable()\n");
            s_error_intr = 2;
        }else
        {
            while (true)
            {
                int err = rt_intr_wait(&s_intr_right, TM_INFINITE);
                if (err >= 0)
                {
                    //detection dephasage
                    //printf("DephD %d \n", s_pinDephR);
                    if (s_pinDephR == 0)
                    {
                        s_countRight++;
                        s_wayRight = pmx::FORWARD;
                    }else
                    {
                        s_countRight--;
                        s_wayRight = pmx::BACK;
                    }
                }else
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
            printf("Error : enabling left deph falling\n");
            s_error_intr = 3;
        }else
        {
            //printf("s_task_L_deph_falling:ok\n");
            while (true)
            {
                int err = rt_intr_wait(&s_intr_L_deph_falling, TM_INFINITE);
                if (err >= 0)
                {
                    s_pinDephL = 0;
                    //printf("s_pinDephL 0\n");
                }else
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
            printf("Error : enabling right deph rising\n");
            s_error_intr = 4;
        }else
        {
            //printf("s_task_L_deph_rising:ok\n");
            while (true)
            {
                int err = rt_intr_wait(&s_intr_L_deph_rising, TM_INFINITE);
                if (err >= 0)
                {
                    s_pinDephL = 1;
                    //printf("s_pinDephL 1\n");
                }else
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
            printf("Error : enabling right deph falling\n");
            s_error_intr = 5;
        }else
        {
            //printf("s_task_R_deph_falling:ok\n");
            while (true)
            {
                int err = rt_intr_wait(&s_intr_R_deph_falling, TM_INFINITE);
                if (err >= 0)
                {
                    s_pinDephR = 0;
                    //printf("s_pinDephR 0\n");
                }else
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
            printf("Error : enabling right deph rising\n");
            s_error_intr = 6;
        }else
        {
            //printf("s_task_R_deph_rising:ok\n");
            while (true)
            {
                int err = rt_intr_wait(&s_intr_R_deph_rising, TM_INFINITE);
                if (err >= 0)
                {
                    s_pinDephR = 1;
                    //printf("s_pinDephR 1\n");
                }else
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
pmx::SensorManager::fireLeftPulse(int value, utils::Chronometer chrono, MotorWay way)
{
    /*if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "fireLeftPulse() [value:" << value << "] [time:" << chrono.getElapsedTimeInMicroSec() << "]" << utils::end;
    }*/
    utils::PointerList <IMotorListener*>::iterator i = this->motorListeners_.begin();
    while (i != motorListeners_.end())
    {
        IMotorListener* listener = *i;
        listener->onLeftPulse(value, chrono, way);
        i++;
    }
}

void
pmx::SensorManager::fireRightPulse(int value, utils::Chronometer chrono, MotorWay way)
{
    /*if (logger().isActive(utils::Level::DEBUG))
    {
        logger().debug() << "fireRightPulse() [value:" << value << "] [time:" << chrono.getElapsedTimeInMicroSec() << "]" << utils::end;
    }*/
    utils::PointerList <IMotorListener*>::iterator i = this->motorListeners_.begin();
    while (i != motorListeners_.end())
    {
        IMotorListener* listener = *i;
        listener->onRightPulse(value, chrono, way);
        i++;
    }
}

void
pmx::SensorManager::execute()
{
    this->executeWithNoBlockingRead();
}

void
pmx::SensorManager::executeWithNoBlockingRead()
{
    logger().debug() << "executeWithNoBlockingRead : SensorManager is started with "
            << this->motorListeners_.size() << " + "
            << this->sensorListeners_.size() << " listener(s)"
            << utils::end;
    pmx::IRobotIn * robotIn = pmx::RobotInOutFactory::instance()->robotIn();

    //Configuration des IRQs (pb avec uniquement le load du fichier !!)
    struct as_gpio_device *pd25, *pd26, *pd19, *pd24, *pd30, *pd29;
    pd25 = as_gpio_open('D', 25);//IMPGD (rising interrupt)
    pd29 = as_gpio_open('D', 29);//IMPDD doublon (falling interrupt)
    pd26 = as_gpio_open('D', 26);//IMPDD (rising interrupt)
    pd30 = as_gpio_open('D', 30);//IMPGD doublon (falling interrupt)
    pd24 = as_gpio_open('D', 24);//IMPG
    pd19 = as_gpio_open('D', 19);//IMPD
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
    }else if (0 != rt_intr_create(&s_intr_right, "IrqRight", 179, 0))
    {
        //printf("rt_intr_create : error for right\n");
        logger().error() << "rt_intr_create : error for right" << utils::end;
        s_task_error = 2;
    }else if (0 != rt_intr_create(&s_intr_R_deph_rising, "IrqRightDephRising", 186, 0))
    {
        //printf("rt_intr_create : error for right deph rising\n");
        logger().error() << "rt_intr_create : error for right deph rising" << utils::end;
        s_task_error = 3;
    }else if (0 != rt_intr_create(&s_intr_R_deph_falling, "IrqRightDephFalling", 190, 0))
    {
        //printf("rt_intr_create : error for right deph falling\n");
        logger().error() << "rt_intr_create : error for right deph falling" << utils::end;
        s_task_error = 4;
    }else if (0 != rt_intr_create(&s_intr_L_deph_rising, "IrqLeftDephRising", 185, 0))
    {
        //printf("rt_intr_create : error for left deph rising\n");
        logger().error() << "rt_intr_create : error for left deph rising" << utils::end;
        s_task_error = 5;
    }else if (0 != rt_intr_create(&s_intr_L_deph_falling, "IrqLeftDephFalling", 189, 0))
    {
        //printf("rt_intr_create : error for left deph falling\n");
        logger().error() << "rt_intr_create : error for left deph falling" << utils::end;
        s_task_error = 6;
    }else if (0 != rt_task_create(&s_server_left, "IrqServerLeft", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for left\n");
        logger().error() << "rt_task_start : error for left" << utils::end;
        s_task_error = 7;
    }else if (0 != rt_task_create(&s_server_right, "IrqServerRight", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for right\n");
        logger().error() << "rt_task_start : error for right" << utils::end;
        s_task_error = 8;
    }else if (0 != rt_task_create(&s_server_R_deph_rising, "IrqServerRightDephRising", TASK_STKSZ, TASK_PRIO, TASK_MODE))
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
    }else
    {
        rt_task_start(&s_server_left, &s_task_left, NULL);
        rt_task_start(&s_server_right, &s_task_right, NULL);
        rt_task_start(&s_server_R_deph_rising, &s_task_R_deph_rising, NULL);
        rt_task_start(&s_server_R_deph_falling, &s_task_R_deph_falling, NULL);
        rt_task_start(&s_server_L_deph_rising, &s_task_L_deph_rising, NULL);
        rt_task_start(&s_server_L_deph_falling, &s_task_L_deph_falling, NULL);

        //affichage LEDINDICATOR
        if(s_task_error == 0)
        {
            pmx::LedIndicator::instance().setOn(4); //ok
        }else
        {
            pmx::LedIndicator::instance().setOff(4); //nok
        }

        //test erreur intr
        if(s_error_intr !=0)
        {
            pmx::LedIndicator::instance().setOff(4); //nok
        }
        int nb;
        while (!stop_)
        {
            if(firePulseEnabled_)
            {
                //traitement des codeurs gauche et droit
                if (s_countLeft != 0) //lance un fire uniquement s'il y a eu une impulsion.
                {
                    fireLeftPulse(s_countLeft, chrono_, s_wayLeft);
                    s_countLeft = 0;
                }
                if (s_countRight != 0)
                {
                    fireRightPulse(s_countRight, chrono_, s_wayRight);
                    //mise à zero des compteurs rightpulse
                    s_countRight = 0;
                }
            }else
            {
                s_countLeft = 0;
                s_countRight = 0;
            }
            
            // Traitement des autres capteurs
            if (sensorListeners_.size() > 0)
            {
                if (logger().isActive(utils::Level::DEBUG))
                {
                    if(nb!=sensorListeners_.size())//si changement de nombre
                    {
                        logger().debug() << "Number of ISensorListener : " << sensorListeners_.size() << utils::end;
                        nb = sensorListeners_.size();
                    }
                }
                utils::PointerList <ISensorListener *>::iterator i = sensorListeners_.begin();
                while (i != sensorListeners_.end())
                {
                    ISensorListener * listener = *i;
                    bool persist = listener->execute(robotIn);

                    if (!persist)
                    {
                        utils::PointerList <ISensorListener *>::iterator old = i;
                        i++;

                        delete listener;
                        sensorListeners_.erase(old);
                    }else
                    {
                        i++;
                    }
                }
            }
        }
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

    logger().info("SensorManager is stopped");
}

