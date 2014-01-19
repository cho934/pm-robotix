#include <Stepper.h>

// Définir le nombre de pas du moteur
#define STEPS 48

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 4, 5, 6, 7);

void setup()
{
  // Initialize random number generator
  randomSeed(analogRead(5));
}

void loop()
{
  // Pick a random direction and distance to move
  int rand = random(-5000, 5000);
  
  // Pick a random speed
  int spd = random(50, 100);
  
  // Go
  stepper.setSpeed(spd);
  stepper.step(rand);
  
  delay(1000); 
}
