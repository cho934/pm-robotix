Retour sur ElecStart

# Codeur à l'aide de moteurs pas à pas #

## Fonctionnement ##

Les codeurs professionnels étant trop coûteux, nous avons essayé de trouver une solution plus adaptée. Après diverses tentatives d'utilisation de roues codeuses de souris sans trop de succès de fiabilité, nous avons étudié puis testé l'utilisation de vieux moteurs pas à pas. '''Ceux-ci ont été récupérés sur de vieux lecteurs de disquettes 5'1/4'''.

Grâce à une petite électronique détectant les faibles impulsions parcourant les bobines lorsque le moteur pas-à-pas est entrainé par la roue motrice, un signal carré est envoyé sur des LEDs, puis vers le robot. Ils sont donc fiables, et totalement hermétiques à la poussière.

Le moteur pas-à-pas étant bipolaire à 6 fils, 48 pas, nous avons même obtenu la quadrature de phase permettant de connaître le sens de rotation.

## Le schéma ##

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecEncoderWithStepperMotor_schema_capture_avec_valeurs.JPG?attredirects=0

## Le résultat ##

Sens anti-horaire :

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecEncoderWithStepperMotor_sens_antihoraire2.jpg?attredirects=0

Sens horaire :

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecEncoderWithStepperMotor_sens_horaire2.jpg?attredirects=0


En revanche en vitesse mini, il s'avère que les signaux ne sont plus symétriques :

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecEncoderWithStepperMotor_vitesse_mini.jpg?attredirects=0

'''CONCLUSION : il faut uniquement utiliser un des fronts et non les deux.'''

## Le typon ##

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecEncoderWithStepperMotor_stepper_pulse_2008_layout.png?attredirects=0https://sites.google.com/site/pmrobotix/home/wiki-img/ElecEncoderWithStepperMotor_stepper_pulse_2008_layout_component.png?attredirects=0

## Photo du mécanisme ##

La roue en bois est solidaire de la roue motrice (roue de roller) et permet d'éviter les poussières amenées par la roue motrice. Un simple élastique maintient le stepper contre la roue en bois.

https://sites.google.com/site/pmrobotix/home/wiki-img/ElecEncoderWithStepperMotor_P1000717_stepper.jpg?attredirects=0

## Les dimensions ##

voir MecaDimGear

## Références ##
  * http://www.pobot.org/Codeur-incremental.html
  * http://www.4qdtec.com/stpen.html

Retour sur ElecStart