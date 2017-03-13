#include <Arduino.h>


#include "Wire.h"
#include "sensors.h"


void setup()
{

  sensor_start();
  Serial.begin(9600);
  mpuStart();
  // TIME_FORMAT myTime;
  // // Change these values to what you want to set your clock to.
  // // You probably only want to set your clock once and then remove
  // // the setDateDs1307 call.
  // myTime.second = 45;
  // myTime.minute = 3;
  // myTime.hour = 7;
  // myTime.dayOfWeek = 5;
  // myTime.dayOfMonth = 17;
  // myTime.month = 4;
  // myTime.year = 8;
  // setDateRTC(myTime);
}

void loop()
{

  S3DVEC rotation;
  measureMagnet();
  delay(500);
  
  
  rotation = getMagnet();
  Serial.println("-------");
  Serial.println(rotation.x);
  Serial.println(rotation.y);
  Serial.println(rotation.z);
}
