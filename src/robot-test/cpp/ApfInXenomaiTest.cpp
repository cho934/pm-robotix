/*!
 * \file
 * \brief Implementation de la classe ApfInXenomaiTest.
 */

#include <iostream>
#include <cstdio>
#include <as_devices/as_gpio.h>
#include <native/task.h>
#include <native/intr.h>
#include <sys/mman.h>
#include "ApfInXenomaiTest.hpp"
#include "Chronometer.hpp"
#include "MotorWay.hpp"

#define TASK_PRIO 99 /* Highest RT priority */
#define TASK_MODE 0 /* No flags */
#define TASK_STKSZ 0 /* Stack size (use default one) */

RT_INTR intr_left;
RT_INTR intr_right;
RT_INTR intr_R_deph_rising;
RT_INTR intr_R_deph_falling;
RT_INTR intr_L_deph_rising;
RT_INTR intr_L_deph_falling;

RT_TASK server_left;
RT_TASK server_right;
RT_TASK server_R_deph_rising;
RT_TASK server_R_deph_falling;
RT_TASK server_L_deph_rising;
RT_TASK server_L_deph_falling;

int countLeft = 0;
int countRight = 0;
pmx::MotorWay wayLeft, wayRight;

int pinDephG = 0, pinDephD = 0;

//pd24 : IMPG
//pd19 : IMPD
//pd25 : IMPGD (rising interrupt)
//pd30 : IMPGD (falling interrupt) doublon
//pd26 : IMPDD (rising interrupt)
//pd29 : IMPDD (falling interrupt) doublon

struct as_gpio_device *pd25, *pd26, *pd19, *pd24, *pd30, *pd29;

extern "C"
{

    void task_left(void*)
    {
        /*! \todo remove printf - use Logger */
        printf("task_left\n");

        if (0 != rt_intr_enable(&intr_left))
        {
        /*! \todo remove printf - use Logger */
            printf("Error : enabling left\n");
            return;
        }

        while (true)
        {
            int err = rt_intr_wait(&intr_left, TM_INFINITE);
            if (err >= 0)
            {
                //detection dephasage
                //printf("DephG %d \n", pinDephG);
                if (pinDephG == 1)
                {
                    countLeft++;
                    wayLeft = pmx::FORWARD;
                }
                else
                {
                    countLeft--;
                    wayLeft = pmx::BACK;
                }
            }
            else
            {
                break; //break si intr en cours de delete.
            }
        }
    }

    void task_L_deph_falling(void*)
    {
        if (0 != rt_intr_enable(&intr_L_deph_falling))
        {
        /*! \todo remove printf - use Logger */
            printf("Error : enabling left deph falling\n");
            return;
        }
        /*! \todo remove printf - use Logger */
        printf("task_L_deph_falling:ok\n");

        while (true)
        {
            int err = rt_intr_wait(&intr_L_deph_falling, TM_INFINITE);
            if (err >= 0)
            {
                pinDephG = 0;
                //printf("pinDephG 0\n");
            }
            else
            {
                break; //break si intr en cours de delete.
            }
        }
    }

    void task_L_deph_rising(void*)
    {
        if (0 != rt_intr_enable(&intr_L_deph_rising))
        {
        /*! \todo remove printf - use Logger */
            printf("Error : enabling right deph rising\n");
            return;
        }
        /*! \todo remove printf - use Logger */
        printf("task_R_deph_rising:ok\n");

        while (true)
        {
            int err = rt_intr_wait(&intr_L_deph_rising, TM_INFINITE);
            if (err >= 0)
            {
                pinDephG = 1;
                //printf("pinDephG 1\n");
            }
            else
            {
                break; //break si intr en cours de delete.
            }
        }
    }

    void task_R_deph_falling(void*)
    {
        if (0 != rt_intr_enable(&intr_R_deph_falling))
        {
        /*! \todo remove printf - use Logger */
            printf("Error : enabling right deph falling\n");
            return;
        }
        /*! \todo remove printf - use Logger */
        printf("task_R_deph_falling:ok\n");

        while (true)
        {
            int err = rt_intr_wait(&intr_R_deph_falling, TM_INFINITE);
            if (err >= 0)
            {
                pinDephD = 0;
                //printf("pinDephD 0\n");
            }
            else
            {
                break; //break si intr en cours de delete.
            }
        }
    }

    void task_R_deph_rising(void*)
    {
        if (0 != rt_intr_enable(&intr_R_deph_rising))
        {
        /*! \todo remove printf - use Logger */
            printf("Error : enabling right deph rising\n");
            return;
        }
        /*! \todo remove printf - use Logger */
        printf("task_R_deph_rising:ok\n");

        while (true)
        {
            int err = rt_intr_wait(&intr_R_deph_rising, TM_INFINITE);
            if (err >= 0)
            {
                pinDephD = 1;
                //printf("pinDephD 1\n");
            }
            else
            {
                break; //break si intr en cours de delete.
            }
        }
    }

    void task_right(void*)
    {
        if (0 != rt_intr_enable(&intr_right))
        {
        /*! \todo remove printf - use Logger */
            printf("Error : enabling right\n");
            return;
        }
        /*! \todo remove printf - use Logger */
        printf("task_right:ok\n");

        while (true)
        {
            int err = rt_intr_wait(&intr_right, TM_INFINITE);
            if (err >= 0)
            {
                //detection dephasage
                //printf("DephD %d \n", pinDephD);

                if (pinDephD == 0)
                {
                    countRight++;
                    wayRight = pmx::FORWARD;
                }
                else
                {
                    countRight--;
                    wayRight = pmx::BACK;
                }
            }
            else
            {
                break; //break si intr en cours de delete.
            }
        }
    }
}

/*
 * ancienen version avec reducteur 150:1 (sur 3sec)
 * left: 543 DephG 1 - right: 535 DephD 0
left: 567 DephG 1 - right: 559 DephD 0
left: 592 DephG 1 - right: 584 DephD 0
left: 617 DephG 1 - right: 608 DephD 0
left: 642 DephG 1 - right: 632 DephD 0
left: 667 DephG 1 - right: 656 DephD 0
left: 692 DephG 1 - right: 681 DephD 0
 *
 * nouvelle version avec reducteur 50:1 (sur 3sec)
 *
 * test::ApfInXenomaiTest INFO left: 1755 wayLeft: FORWARD right: 1706 wayRight: FORWARD
test::ApfInXenomaiTest INFO left: 1826 wayLeft: FORWARD right: 1774 wayRight: FORWARD
test::ApfInXenomaiTest INFO left: 1896 wayLeft: FORWARD right: 1841 wayRight: FORWARD
test::ApfInXenomaiTest INFO left: 1968 wayLeft: FORWARD right: 1909 wayRight: FORWARD
test::ApfInXenomaiTest INFO left: 2038 wayLeft: FORWARD right: 1977 wayRight: FORWARD
 *
 */
void test::ApfInXenomaiTest::run(int, char *[])
{

    logger().info() << "test::ApfInXenomaiTest: Run" << utils::end;


    //ouverture des pin de dephasage
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


    //Pour un test en front montant et descendant, 2 méthodes :
    // 1. utiliser 2 Gpios, l'une en posedge, l'autre en negedge
    // 2. changer la polarité de l'IT à chaque trigger => pas assez rapide :
    //changer le trigger prend 700 à 800 us avec la fonction as_gpio_set_irq_mode().

    mlockall(MCL_CURRENT | MCL_FUTURE);

    //info IRQ=>GPIO
    //70=>PA6 ; 179=>PD19; 184=>PD24 ; 185=>PD25 ; 186=>PD26 ; 189=>PD29 ; 190=>PD30

    if (0 != rt_intr_create(&intr_left, "IrqLeft", 184, 0))
    {
        //printf("rt_intr_create : error for left\n");
        logger().error() << "rt_intr_create : error for left" << utils::end;
    }
    else if (0 != rt_intr_create(&intr_right, "IrqRight", 179, 0))
    {
        //printf("rt_intr_create : error for right\n");
        logger().error() << "rt_intr_create : error for right" << utils::end;
    }
    else if (0 != rt_intr_create(&intr_R_deph_rising, "IrqRightDephRising", 186, 0))
    {
        //printf("rt_intr_create : error for right deph rising\n");
        logger().error() << "rt_intr_create : error for right deph rising" << utils::end;
    }
    else if (0 != rt_intr_create(&intr_R_deph_falling, "IrqRightDephFalling", 190, 0))
    {
        //printf("rt_intr_create : error for right deph falling\n");
        logger().error() << "rt_intr_create : error for right deph falling" << utils::end;
    }
    else if (0 != rt_intr_create(&intr_L_deph_rising, "IrqLeftDephRising", 185, 0))
    {
        //printf("rt_intr_create : error for left deph rising\n");
        logger().error() << "rt_intr_create : error for left deph rising" << utils::end;
    }
    else if (0 != rt_intr_create(&intr_L_deph_falling, "IrqLeftDephFalling", 189, 0))
    {
        //printf("rt_intr_create : error for left deph falling\n");
        logger().error() << "rt_intr_create : error for left deph falling" << utils::end;
    }
    else if (0 != rt_task_create(&server_left, "IrqServerLeft", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for left\n");
        logger().error() << "rt_task_start : error for left" << utils::end;
    }
    else if (0 != rt_task_create(&server_right, "IrqServerRight", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for right\n");
        logger().error() << "rt_task_start : error for right" << utils::end;
    }
    else if (0 != rt_task_create(&server_R_deph_rising, "IrqServerRightDephRising", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for right deph rising\n");
        logger().error() << "rt_task_start : error for right deph rising" << utils::end;
    }
    else if (0 != rt_task_create(&server_R_deph_falling, "IrqServerRightDephFalling", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for right deph falling\n");
        logger().error() << "rt_task_start : error for right deph falling" << utils::end;
    }
    else if (0 != rt_task_create(&server_L_deph_rising, "IrqServerLeftDephRising", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for left deph rising\n");
        logger().error() << "rt_task_start : error for left deph rising" << utils::end;
    }
    else if (0 != rt_task_create(&server_L_deph_falling, "IrqServerLeftDephFalling", TASK_STKSZ, TASK_PRIO, TASK_MODE))
    {
        //printf("rt_task_start : error for left deph falling\n");
        logger().error() << "rt_task_start : error for left deph falling" << utils::end;
    }
    else
    {
        logger().debug() << "start task" << utils::end;
        rt_task_start(&server_left, &task_left, NULL);
        rt_task_start(&server_right, &task_right, NULL);
        rt_task_start(&server_R_deph_rising, &task_R_deph_rising, NULL);
        rt_task_start(&server_R_deph_falling, &task_R_deph_falling, NULL);
        rt_task_start(&server_L_deph_rising, &task_L_deph_rising, NULL);
        rt_task_start(&server_L_deph_falling, &task_L_deph_falling, NULL);

        utils::Chronometer chrono;
        chrono.start();
        long now = chrono.getElapsedTimeInMicroSec();

        long start = now;
        logger().debug() << "while" << utils::end;

        long stop = start + 3000 * 1000;
        while (now < stop)
        {
            usleep(100000); //optimisation de l'attente. 
            now = chrono.getElapsedTimeInMicroSec();
            //printf("left: %d DephG %d - right: %d DephD %d \n", countLeft, wayLeft, countRight, wayRight);
            logger().info() << "left: " << countLeft << " wayLeft: " << (wayLeft == pmx::FORWARD ? "FORWARD" : "BACK") << " right: " << countRight << " wayRight: " << (wayRight == pmx::FORWARD ? "FORWARD" : "BACK") << utils::end;
        }

        rt_intr_delete(&intr_left);
        rt_intr_delete(&intr_right);
        rt_intr_delete(&intr_R_deph_rising);
        rt_intr_delete(&intr_R_deph_falling);
        rt_intr_delete(&intr_L_deph_rising);
        rt_intr_delete(&intr_L_deph_falling);

        rt_task_delete(&server_left);
        rt_task_delete(&server_right);
        rt_task_delete(&server_R_deph_rising);
        rt_task_delete(&server_R_deph_falling);
        rt_task_delete(&server_L_deph_rising);
        rt_task_delete(&server_L_deph_falling);

        logger().debug() << "END : countLeft: " << countLeft << " countRight: " << countRight << utils::end;
    }
}
