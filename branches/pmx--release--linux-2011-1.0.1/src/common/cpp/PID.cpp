/*!
 * \file
 * \brief Implémentation de la classe PID.
 */

#include <cmath>
#include "PID.hpp"

utils::PID::PID()
: kP_(0), kI_(0), kD_(0)
{}

utils::PID::PID(double kP, double kI, double kD)
: kP_(kP), kI_(kI), kD_(kD), lastError_(0), errSum_(0)
{}

utils::PID::PID(int kP, int kI, int kD)
: kP_(kP), kI_(kI), kD_(kD), lastError_(0), errSum_(0)
{}

utils::PID::PID(const utils::PID & pid)
: kP_(pid.kP_), kI_(pid.kI_), kD_(pid.kD_), lastError_(0), errSum_(0)
{}

double
utils::PID::ComputePID(int error)
{  
    double P, I, D;
    
    errSum_ += error; //somme des erreurs depuis le début
     
    double errDif = error - lastError_;
    lastError_ = error;

    P = error * kP_;   // Proportionnel
    I = errSum_ * kI_; // Intégrale
    D = errDif * kD_;  // Dérivée
    logger().debug() << "error:" << error << " errSum_:" << errSum_ << " errDif:" << errDif << " kP_:" << kP_ << " kI_:" << kI_ << " kD_:" << kD_<< utils::end;
    return P + I + D; // Le résultat est la somme des 3 composantes calculées.
}

void
utils::PID::reset()
{
    this->lastError_ = 0;
    this->errSum_ = 0;
}
