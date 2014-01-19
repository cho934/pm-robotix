/*  Digital Pin 2 accepts external interrupts. Pin1 of a rotary encoder
    is attached to DigitalPin2. An interrupt routine will be called
    when pin1 changes state, including noise.
    This will be made more efficient with hardware debouncing.
    */
int pin1 = 2;
int pin2 = 3;
int counter;
boolean goingUp = false;
boolean goingDown = false;
void setup()
{
  counter = 0;
  //Serial prints for debugging and testing
  Serial.begin(9600);

/* Setup encoder pins as inputs */
    pinMode(pin1, INPUT); // Pin 2
    pinMode(pin2, INPUT); // Pin 4 

// encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, decoder, FALLING);

}

void loop()
{
//using while statement to stay in the loop for continuous
//interrupts
while(goingUp==1) // CW motion in the rotary encoder
{
goingUp=0; // Reset the flag
counter ++;
Serial.println(counter);
}

while(goingDown==1) // CCW motion in rotary encoder
{
goingDown=0; // clear the flag
counter --;
Serial.println(counter);
}
}

void decoder()
//very short interrupt routine 
//Remember that the routine is only called when pin1
//changes state, so it's the value of pin2 that we're
//interrested in here
{
if (digitalRead(pin1) == digitalRead(pin2))
{
goingUp = 1; //if encoder channels are the same, direction is CW
}
else
{
goingDown = 1; //if they are not the same, direction is CCW
}
}
