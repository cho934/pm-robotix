#include <cmath>
#include <iostream>
#include "PositionTest.hpp"

void
test::PositionTest::testPosition()
{
    pmx::Position position;
    assert(position.x() == 0.0, "Erreur dans l'initialisation de 'x' par le constructeur par défaut");
    assert(position.y() == 0.0, "Erreur dans l'initialisation de 'y' par le constructeur par défaut");
    assert(position.angle() == 0.0, "Erreur dans l'initialisation de 'angle' par le constructeur par défaut");
    
    pmx::Position position2(10.0, 20.0, 3.0 * M_PI);
    assert(position2.x() == 10.0, "Erreur dans l'initialisation de 'x' par le constructeur initialisé");
    assert(position2.y() == 20.0, "Erreur dans l'initialisation de 'y' par le constructeur initialisé");
    assert(position2.angle() == M_PI, "Erreur dans l'initialisation de 'angle' par le constructeur initialisé");
    
    position = pmx::Position(30.0, 40.0, M_PI);
    assert(position.x() == 30.0, "Erreur dans l'initialisation de 'x' par l'opérateur de recopie");
    assert(position.y() == 40.0, "Erreur dans l'initialisation de 'y' par l'opérateur de recopie");
    assert(position.angle() == M_PI, "Erreur dans l'initialisation de 'angle' par l'opérateur de recopie");
}

void
test::PositionTest::testRotate()
{
    pmx::Position position(10.0, 20.0, 0.0);
    position = position.rotate(M_PI);
    assert(position.x() == 10.0, "La méthode rotate() modifie 'x'");
    assert(position.y() == 20.0, "La méthode rotate() modifie 'y'");
    assert(position.angle() == M_PI, "La méthode rotate() n'initialise pas correctement 'angle'");
}
