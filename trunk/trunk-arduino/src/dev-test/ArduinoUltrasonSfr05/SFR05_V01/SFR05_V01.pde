//////////////////////////////////////////////////////////////////////////////////////////
/*
   Télémètre à ultrasons SRF05 + Buzzer piézo-électrique
   http://labo.serandour.com
*/
//////////////////////////////////////////////////////////////////////////////////////////

// Les entrées / sorties utilisées
int dPinSRF05 = 8;    // Trigger Input, Echo Output sur l'entrée/sortie digitale 8.

int distanceMin = 20; // en cm


//////////////////////////////////////////////////////////////////////////////////////////
// Initialisation
//////////////////////////////////////////////////////////////////////////////////////////

void setup()
{  
  Serial.begin(9600);
  
}

//////////////////////////////////////////////////////////////////////////////////////////
// Boucle principale
//////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  int distanceObstacle = distanceMesuree();
  Serial.println(distanceObstacle);
  if (distanceObstacle < distanceMin) {
    Serial.println("<20");
  } 
}


//////////////////////////////////////////////////////////////////////////////////////////
// Effectuer une mesure avec le capteur à ultrasons
//////////////////////////////////////////////////////////////////////////////////////////

int distanceMesuree()
{
  pinMode(dPinSRF05, OUTPUT);
  // Make sure pin is low before sending a short high to trigger ranging.
  digitalWrite(dPinSRF05, LOW);
  delayMicroseconds(2);
  // Send a short 10 microseconds high burst on pin to start ranging.
  digitalWrite(dPinSRF05, HIGH);
  delayMicroseconds(10);
  // Send pin low again before waiting for pulse back in.
  digitalWrite(dPinSRF05, LOW);
  
  pinMode(dPinSRF05, INPUT);
  // Reads echo pulse in from SRF05 in microseconds.
  int duree = pulseIn(dPinSRF05, HIGH);
  // On doit attendre 50 ms avant le prochain signal de déclenchement.
  delay(50);  
   
  int distance = duree / 58;  // On divise par 58 pour avoir une distance en cm.
  return(distance);
}



//////////////////////////////////////////////////////////////////////////////////////////

