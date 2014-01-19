/*!
 * \file
 * \brief Implémentation de la classe Stepper.
 * \deprecated
 */

#include "Stepper.hpp"
#include "Robot.hpp"
#include "RobotInOutFactory.hpp"

pmx::StepperAction::StepperAction(pmx::Stepper & stepper)
: stepper_(stepper)
{}

pmx::Stepper::Stepper(pmx::Robot & robot, ushort dm)
: ARobotElement(robot), active_(false), dm_(dm), step_(0)
{
    logger().debug() << "Stepper::Stepper()" << utils::end;
    
    values_[0] = pmx::IRobotOut::PIN1;
    values_[1] = pmx::IRobotOut::PIN0;
    values_[2] = pmx::IRobotOut::PIN3;
    values_[3] = pmx::IRobotOut::PIN2;
    values_[4] = pmx::IRobotOut::PIN0;
    values_[5] = pmx::IRobotOut::PIN1;
    values_[6] = pmx::IRobotOut::PIN2;
    values_[7] = pmx::IRobotOut::PIN3;
    
}

bool pmx::StepperAction::execute(IRobotOut * out)
{
    bool val = false;
    if (stepper_.active())
    {
        logger().debug() << "actif" << utils::end;
        //utilisation pour le test des PIN 0,1,2,3
        //TABLE DE VERITE
        //0101              
        //0001 (demi pas)   PIN1 à 0
        //1001              PIN0 à 1
        //1000 (demi pas)   PIN3 à 0
        //1010              PIN2 à 1
        //0010 (demi pas)   PIN0 à 0
        //0110              PIN1 à 1
        //0100 (demi pas)   PIN2 à 0
        //                  PIN3 à 1
        
        if(stepper_.step() == 0)
        {
            // init
            logger().debug() << "init" << utils::end;
            out->setValues(stepper_.dm(), 0);
            
            
            stepper_.step(1);
        }else
        {
            while(stepper_.active())
            {
                /*
                //variante 1 :  Commande par pas entiers, une seule phase alimentée à la fois sens anti-horaire
                //1000 (1010) 0010 (0110) 0100 (0101) 0001 (1001)
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN3, 0);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN0, 1);
                logger().debug() << "step:1000" << utils::end;
                
                usleep(10000);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN0, 0);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN2, 1);
                logger().debug() << "step:0010" << utils::end;
                
                usleep(10000);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN2, 0);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN1, 1);
                logger().debug() << "step:0100" << utils::end;
                
                usleep(10000);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN1, 0);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN3, 1);
                logger().debug() << "step:0001" << utils::end;
                
                usleep(10000);
                */
                
                
                /*
                //variante 2 :  Commande par pas entiers, 2 phases alimentée en meme temps sens anti-horaire
                //1010 0110 0101 1001
                
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN0, 1);

                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN2, 1);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN3, 0);
                
                logger().debug() << "step:1010" << utils::end;
                
                usleep(10000);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN0, 0);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN1, 1);
                logger().debug() << "step:0110" << utils::end;
                
                usleep(10000);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN2, 0);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN3, 1);
                logger().debug() << "step:0101" << utils::end;
                
                usleep(10000);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN1, 0);
                out->setValue(stepper_.dm(), pmx::IRobotOut::PIN0, 1);
                logger().debug() << "step:1001" << utils::end;
                
                usleep(10000);
                */
                
                
                //suivant la table de vérité, incrémentation
                logger().debug() << "step:" << stepper_.step() << " value:" << stepper_.values_[stepper_.step()-1] << " val:" << val << utils::end;
                    
                out->setValue(stepper_.dm(), stepper_.values_[stepper_.step()-1], val);
                
                usleep(100);
                if (val){val = false;}else{val = true;}
                if(stepper_.step() >= 8)
                {
                    stepper_.step(1);
                }else
                {
                    stepper_.step(stepper_.step() + 1);
                }      
                 
            }
        }             
    }else
    {
        out->setValues(stepper_.dm(), 0);
    }
    return true;
}
