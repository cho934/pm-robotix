/**
 * Test I2C master (arduino) used to send text to a salve rainboduino  
 */

#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
}

void loop()
{
  sendText(4, "C EST GAGNE  ");
  delay(30000);

  sendText(4, "OUI DIDITE!  ");
  delay(30000);

  // no text
  sendText(4, " ");
  delay(10000);
  
}

void sendText(int salveAdress, char* text)
{
  Wire.beginTransmission(salveAdress);
  Wire.write(text);
  Wire.endTransmission();    // stop transmitting
}
