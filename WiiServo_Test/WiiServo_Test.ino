#include <Wiichuck.h>
#include <Wire.h>
#include <Servo.h> 

Wiichuck wii;
Servo horzServo;  
Servo vertServo;
const int horzServoPin = 11;
const int vertServoPin = 9;
int nhorzPos = 90;
int nvertPos = 90;
int njoyX = 132;
int njoyY = 132;

//220 max
// 40 min
// 128-135 or so normal

void setup() {
  Serial.begin(9600);
  horzServo.attach(horzServoPin);
  vertServo.attach(vertServoPin);
  
  wii.init();  
  wii.calibrate();  // calibration
}

void loop() {
  if (wii.poll()) {
//int njoyX = wii.joyX();
//int  njoyY = wii.joyY();
    
    nhorzPos = map(wii.joyX(), 35, 230, 170, 40);
    nvertPos = map(wii.joyY(), 35, 230, 40, 170);
    
//    
//    if (njoyX > 200) {
//      // turn servo right
//       if (nhorzPos < 180) {
//         nhorzPos = nhorzPos+2;
//       }
//    } else if (njoyX < 40) {
//      // turn servo left
//      if (nhorzPos > 30) {
//        nhorzPos = nhorzPos-2; 
//      }
//    }  
//
//    if (njoyY > 200) {
//      // turn servo up 
//      if (nvertPos < 178) {
//         nvertPos = nvertPos+2;
//       }
//    } else if (njoyY < 40) {
//      // turn servo down  
//      if (nvertPos > 30) {
//        nvertPos = nvertPos-2; 
//      }
//    }
    
    horzServo.write(nhorzPos);
    vertServo.write(nvertPos);
    Serial.print("joy X: ");Serial.println(njoyX);
    Serial.print("joy y: ");Serial.println(njoyY);
    //Serial.print("joy X: ");Serial.println(nhorzPos);
    //Serial.print("joy y: ");Serial.println(nvertPos);

    
    delay(10); 
  }
}
