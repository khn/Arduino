#include <Wire.h>
#include <Servo.h> 
#include <Math.h>
#include <Arduino.h>
#include "nunchuck_funcs.h"
Servo myservo1;
Servo myservo2;
int x=0;
int y=0;
void setup()
{
  myservo1.attach(11);
  myservo2.attach(9);
  nunchuck_setpowerpins();
  nunchuck_init();
  myservo1.write(90);
  myservo2.write(90);
  Serial.begin(9600);
}
void loop()
{
  nunchuck_get_data(); 
  x=nunchuck_joyx();
  y=nunchuck_joyy();
  // X axis
  if(x > 200)
   myservo1.write(0);
  else if(x < 40)
   myservo1.write(180);
  else
   myservo1.write(90);
  Serial.print("joy X: ");Serial.println(nunchuck_joyx());
  
  
  // Y axis
  if(y > 200)
   myservo2.write(0);
  else if(y < 40)
   myservo2.write(180);
  else
   myservo2.write(90);
  Serial.print("joy Y: ");Serial.println(nunchuck_joyy());
  
}
