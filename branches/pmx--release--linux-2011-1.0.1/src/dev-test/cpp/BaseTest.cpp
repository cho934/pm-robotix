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
