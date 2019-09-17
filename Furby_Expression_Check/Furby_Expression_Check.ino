#include <Wire.h>
#include <SPI.h>

/***
   Red - VCC
   Brown - Ground
   orange - cam home
   yellow - Gear Rotation
   Green - Back
   Blue - reset
   purple - feed
   Gray - revers
   white forward
   black - LED
***/


#define XCAM_HOME  7
#define MOTOR_FORWARD 3
#define MOTOR_REVERSE 2
#define XCAM_SENSOR 8


int nCamPosition = 0; // Keeps track of



void setup() {
  // put your setup code here, to run once:

  pinMode( XCAM_HOME, INPUT );
  digitalWrite( XCAM_HOME, HIGH ); //pullup
  pinMode( XCAM_SENSOR, INPUT );
  digitalWrite( XCAM_SENSOR, LOW ); //pulldown

  pinMode( MOTOR_FORWARD, OUTPUT );
  digitalWrite( MOTOR_FORWARD, HIGH );
  pinMode( MOTOR_REVERSE, OUTPUT );
  digitalWrite( MOTOR_FORWARD, LOW );
  Serial.begin(9600);

} // setup

// put your main code here, to run repeatedly:
void loop() {
  if (digitalRead(XCAM_HOME) == LOW) {
    nCamPosition = 0;
  }
  digitalWrite( MOTOR_FORWARD, HIGH );
  while (digitalRead(XCAM_SENSOR) == LOW) {
    delay(1);
  }
  digitalWrite( MOTOR_FORWARD, LOW );
  Serial.println(nCamPosition);
  delay(300);
nCamPosition++;
  digitalWrite( MOTOR_FORWARD, HIGH );
  while (digitalRead(XCAM_SENSOR) == HIGH) {
    delay(1);
  }
} // loop






