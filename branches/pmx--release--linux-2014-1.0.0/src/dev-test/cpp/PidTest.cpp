/*!
 * \file
 * \brief Implémentation de la classe PidTest.
 */

#include "PidTest.hpp"

void
test::PidTest::testGetters()
{
    utils::PID pid(1, 2, 3);
    this->assert(pid.getkP() == 1, "Le getter getkP() ne retourne pas la valeur de kP");
    this->assert(pid.getkI() == 2, "Le getter getkI() ne retourne pas la valeur de kI");
    this->assert(pid.getkD() == 3, "Le getter getkD() ne retourne pas la valeur de kD");
}

void
test::PidTest::testComputePIDForP()
{
    utils::PID pid(1, 0, 0);
    for(int i = 10 ; i <= 0 ; i++)
    {
        double result = pid.ComputePID(i);
        if(result != i)
        {
            fail("Pid non fonctionnel pour kP=1, kI=0, kD=0");
            logger().debug() << "valeur : " << result << " au lieu de " << i << utils::end;
        }
    }
}

void
test::PidTest::testComputePIDForI()
{
    utils::PID pid(0, 1, 0);
    double result1 = pid.ComputePID(10);
    if(result1 != 10)
    {
        fail("Pid non fonctionnel pour kP=0, kI=1, kD=0");
        logger().debug() << "valeur : " << result1 << " au lieu de 10" << utils::end;
    }

    double result2 = pid.ComputePID(0);
    if(result2 != 10)
    {
        fail("Pid non fonctionnel pour kP=0, kI=1, kD=0");
        logger().debug() << "valeur : " << result2 << " au lieu de 10" << utils::end;
    }

    double result3 = pid.ComputePID(-10);
    if(result3 != 0)
    {
        fail("Pid non fonctionnel pour kP=0, kI=1, kD=0");
        logger().debug() << "valeur : " << result3 << " au lieu de 0" << utils::end;
    }
}

void
test::PidTest::testComputePIDForD()
{
    utils::PID pid(0, 0, 1);
    double result1 = pid.ComputePID(10);
    if(result1 != 10)
    {
        fail("Pid non fonctionnel pour kP=0, kI=1, kD=0");
        logger().debug() << "valeur : " << result1 << " au lieu de 10" << utils::end;
    }

    double result2 = pid.ComputePID(0);
    if(result2 != -10)
    {
        fail("Pid non fonctionnel pour kP=0, kI=1, kD=0");
        logger().debug() << "valeur : " << result2 << " au lieu de -10" << utils::end;
    }

    double result3 = pid.ComputePID(10);
    if(result3 != 10)
    {
        fail("Pid non fonctionnel pour kP=0, kI=1, kD=0");
        logger().debug() << "valeur : " << result3 << " au lieu de 10" << utils::end;
    }
}

void
test::PidTest::suite()
{
    logger().debug() << "PidTest : Go" << utils::end;
    testGetters();
    testComputePIDForP();
    testComputePIDForI();
    testComputePIDForD();
}
