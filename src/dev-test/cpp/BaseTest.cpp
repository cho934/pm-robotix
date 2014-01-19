/*!
 * \file
 * \brief Implémentation de la classe BaseTest.
 */

#include "BaseTest.hpp"
#include "Robot.hpp"
#include "Base.hpp"
#include "UnitTest.hpp"

using namespace pmx;

void
test::BaseTest::suite()
{
    this->testVecteurCorrectionEnabled();
    this->testPidPositionEnabled();
    this->testPidSpeedEnabled();
    this->testComputeDestionationVector();
    this->testComputeAngleToGo();
}

void
test::BaseTest::testVecteurCorrectionEnabled()
{
    Robot robot;
    Base base(robot);

    this->assert(!base.vecteurCorrectionEnabled(), "vecteurCorrectionEnabled ne vaut pas false par défaut");

    base.vecteurCorrectionEnabled(true);
    this->assert(base.vecteurCorrectionEnabled(), "vecteurCorrectionEnabled n'est pas défini correctement [actif]");
    this->assert(!base.pidPositionEnabled(), "vecteurCorrectionEnabled impacte pidPositionEnabled [actif]");
    this->assert(!base.pidSpeedEnabled(), "vecteurCorrectionEnabled impacte pidSpeedEnabled [actif]");

    base.vecteurCorrectionEnabled(false);
    this->assert(!base.vecteurCorrectionEnabled(), "vecteurCorrectionEnabled n'est pas défini correctement [inactif]");
    this->assert(!base.pidPositionEnabled(), "vecteurCorrectionEnabled impacte pidPositionEnabled [inactif]");
    this->assert(!base.pidSpeedEnabled(), "vecteurCorrectionEnabled impacte pidSpeedEnabled [inactif]");
}

void
test::BaseTest::testPidPositionEnabled()
{
    Robot robot;
    Base base(robot);

    this->assert(!base.pidPositionEnabled(), "pidPositionEnabled ne vaut pas false par défaut");

    base.pidPositionEnabled(true);
    this->assert(base.pidPositionEnabled(), "pidPositionEnabled n'est pas défini correctement [actif]");
    this->assert(!base.vecteurCorrectionEnabled(), "pidPositionEnabled impacte vecteurCorrectionEnabled [actif]");
    this->assert(!base.pidSpeedEnabled(), "pidPositionEnabled impacte pidSpeedEnabled [actif]");

    base.pidPositionEnabled(false);
    this->assert(!base.pidPositionEnabled(), "pidPositionEnabled n'est pas défini correctement [inactif]");
    this->assert(!base.vecteurCorrectionEnabled(), "pidPositionEnabled impacte vecteurCorrectionEnabled [inactif]");
    this->assert(!base.pidSpeedEnabled(), "pidPositionEnabled impacte pidSpeedEnabled [inactif]");
}

void
test::BaseTest::testPidSpeedEnabled()
{
    Robot robot;
    Base base(robot);

    this->assert(!base.pidSpeedEnabled(), "pidSpeedEnabled ne vaut pas false par défaut");

    base.pidSpeedEnabled(true);
    this->assert(base.pidSpeedEnabled(), "pidSpeedEnabled n'est pas défini correctement [actif]");
    this->assert(!base.pidPositionEnabled(), "pidSpeedEnabled impacte pidPositionEnabled [actif]");
    this->assert(!base.vecteurCorrectionEnabled(), "pidSpeedEnabled impacte vecteurCorrectionEnabled [actif]");

    base.pidSpeedEnabled(false);
    this->assert(!base.pidSpeedEnabled(), "pidSpeedEnabled n'est pas défini correctement [inactif]");
    this->assert(!base.pidPositionEnabled(), "pidSpeedEnabled impacte pidPositionEnabled [inactif]");
    this->assert(!base.vecteurCorrectionEnabled(), "pidSpeedEnabled impacte vecteurCorrectionEnabled [inactif]");
}

void
test::BaseTest::testComputeDestionationVector()
{
    Robot robot;

    double *v = new double[4];


    robot.position().x(100.0);
    robot.position().y(100.0, pmx::PMXRED);
    robot.position().angle(0.0, pmx::PMXRED);
    robot.base().computeDestinationVector(v, 200.0, 200.0, robot.position().x(), robot.position().y());
    logger().debug() << "vx: " << v[0]
            << " vy: " << v[1]
            << " vd: " << v[2]
            << " va: " << v[3]
            << " va: " << v[3]*180/M_PI
            << utils::end;
    this->assert(v[0]==100.0, "vx [NOK]");
    this->assert(v[1]==100.0, "vy [NOK]");
    this->assert(v[2]==(std::pow(std::pow(v[0], 2) + std::pow(v[1], 2), 0.5)), "vd [NOK]");
    this->assert((int)(v[3]*180/M_PI)==45, "va 45 [NOK]");


    robot.position().x(-100.0);
    robot.position().y(-50.0, pmx::PMXRED);
    robot.position().angle(10.0, pmx::PMXRED);
    robot.base().computeDestinationVector(v, -200.0, -200.0, robot.position().x(), robot.position().y());
    logger().debug() << "vx: " << v[0]
            << " vy: " << v[1]
            << " vd: " << v[2]
            << " va: " << v[3]
            << " va: " << v[3]*180/M_PI
            << utils::end;
    this->assert(v[0]==-100.0, "vx [NOK]");
    this->assert(v[1]==-150.0, "vy [NOK]");
    this->assert(v[2]==(std::pow(std::pow(v[0], 2) + std::pow(v[1], 2), 0.5)), "vd [NOK]");
    this->assert((int)(v[3]*180/M_PI)==-123, "va -123 [NOK]");

    delete[] v;
}

void
test::BaseTest::testComputeAngleToGo()
{
    Robot robot;
    double diffAngle = 0.0;

    robot.position().x(200.0);
    robot.position().y(100.0, pmx::PMXRED);
    robot.position().angle(0.0, pmx::PMXRED);
    diffAngle = robot.base().computeAngleToGo(M_PI_2);
    logger().debug() 
            << " x: 200" 
            << " y: 100" 
            << " a: 0" 
            << " diffAngle: " << diffAngle
            << " diffAngle: " << diffAngle*180/M_PI
            << utils::end;
    this->assert((diffAngle*180/M_PI)==90, "diffAngle [NOK]");

    robot.position().x(200.0);
    robot.position().y(100.0, pmx::PMXRED);
    robot.position().angle(0.0, pmx::PMXRED);
    diffAngle = robot.base().computeAngleToGo(100*M_PI/180);
    logger().debug()
            << " x: 200"
            << " y: 100"
            << " a: 0"
            << " diffAngle: " << diffAngle
            << " diffAngle: " << diffAngle*180/M_PI
            << utils::end;
    this->assert((diffAngle*180/M_PI)==100, "diffAngle [NOK]");

    robot.position().x(200.0);
    robot.position().y(100.0, pmx::PMXRED);
    robot.position().angle(0.0, pmx::PMXRED);
    diffAngle = robot.base().computeAngleToGo(100*M_PI/180);
    logger().debug()
            << " x: 200"
            << " y: 100"
            << " a: 0"
            << " diffAngle: " << diffAngle
            << " diffAngle: " << diffAngle*180/M_PI
            << utils::end;
    this->assert((diffAngle*180/M_PI)==-100, "diffAngle [NOK]");

    robot.position().x(200.0);
    robot.position().y(100.0, pmx::PMXRED);
    robot.position().angle(0.0, pmx::PMXRED);
    diffAngle = robot.base().computeAngleToGo(-180*M_PI/180);
    logger().debug()
            << " x: 200"
            << " y: 100"
            << " a: 0"
            << " diffAngle: " << diffAngle
            << " diffAngle: " << diffAngle*180/M_PI
            << utils::end;
    this->assert((diffAngle*180/M_PI)==-180, "diffAngle [NOK]");

    robot.position().x(200.0);
    robot.position().y(100.0, pmx::PMXRED);
    robot.position().angle(0.0, pmx::PMXRED);
    diffAngle = robot.base().computeAngleToGo(180*M_PI/180);
    logger().debug()
            << " x: 200"
            << " y: 100"
            << " a: 0"
            << " diffAngle: " << diffAngle
            << " diffAngle: " << diffAngle*180/M_PI
            << utils::end;
    this->assert((diffAngle*180/M_PI)==180, "diffAngle [NOK]");


}

