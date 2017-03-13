#include <Arduino.h>


#include "Wire.h"
#include "sensors_lib.h"




void setup()
{
  sensor_start();
  Serial.begin(9600);
  initLSMAccel();
}

void loop()
{

  S3DVEC rotation;
  delay(500);
  
  
  rotation = getLSMAccel();
  Serial.println("-------");
  Serial.println(rotation.x, HEX);
  Serial.println(rotation.y, HEX);
  Serial.println(rotation.z, HEX);
}
