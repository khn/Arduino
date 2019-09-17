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
  //Serial.begin(9600);

} // setup

unsigned motorForwardP = 1;
// put your main code here, to run repeatedly:
void loop() {
  //  if (digitalRead(XCAM_HOME) == LOW) {
  //    nCamPosition = 0;
  //    // Serial.println("RESET");
  //   // delay(100);
  //    moveReverse();
  //  }
  //  if (digitalRead(XCAM_SENSOR) == HIGH) {
  //    if (digitalRead(MOTOR_FORWARD) == HIGH)
  //    {
  //      nCamPosition++ ;
  //    } else {
  //      nCamPosition-- ;
  //    }
  //  }
  // updateMotorFromButton();
  keepTrackOfPostion();
  /* From 45 go forward to 0
     then go backwards from 0 to 45*/

  if (nCamPosition == 42 )
  {
    moveForward();
  }

  if (nCamPosition == 0 ) {
    moveReverse();
    while (nCamPosition > 45) {
      keepTrackOfPostion();
      delay(2);
    }
  }

 delay(2);


/*
  else if (nCamPosition >= 30 ) {
    // digitalWrite(MOTOR_FORWARD, LOW);
    //delay(2000);
    moveReverse();
  }
  // Serial.println(nCamPosition);
  // Serial.println(digitalRead(XCAM_SENSOR));
  delay(3);*/
} // loop

void keepTrackOfPostion()
{
  if (digitalRead(XCAM_HOME) == LOW) {
    nCamPosition = 0;
    // Serial.println("RESET");
    // delay(100);
    moveForward();
  }
  if (digitalRead(XCAM_SENSOR) == HIGH) {
    if (digitalRead(MOTOR_FORWARD) == HIGH)
    {
      nCamPosition++ ;
    } else {
      nCamPosition-- ;
    }
  }

}


/* read button and set variables accordingly */
void updateMotorFromButton()
{
  char forwardButton = (digitalRead(MOTOR_FORWARD) == LOW);
  char reverseButton = (digitalRead(MOTOR_REVERSE) == LOW);

  // don't do anything if both are pressed
  if (forwardButton && reverseButton) return;

  if (forwardButton) {
    motorForwardP = 1;
    moveForward();
  }

  if (reverseButton) {
    motorForwardP = 0;
    moveReverse();
  }




} // updateMotorFromButton

// set motor pins to move forward
void moveForward()
{
  digitalWrite(MOTOR_REVERSE, LOW);
  digitalWrite(MOTOR_FORWARD, HIGH);
  ///nCamPosition++;
} // moveForward

// set motor pins to move reverse
void moveReverse()
{
  digitalWrite(MOTOR_FORWARD, LOW);
  digitalWrite(MOTOR_REVERSE, HIGH);
  // nCamPosition--;
} // moveReverse





