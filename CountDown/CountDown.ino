#include <DigitShield.h>
float counter = 99;
int d = 10;
int Red = 1;
int Orange = 3;
int White = 5;
int Boom = 0;
int Speed = 0;
int Done = 0;

void setup() {
  Serial.begin(9600); 
  DigitShield.begin();
  DigitShield.setPrecision(2);
  pinMode(7, INPUT);
  pinMode(1, INPUT);
  pinMode(0, INPUT);
}

void loop() {
//  Boom = analogRead(Red);
//  Speed  = analogRead(Orange);
//      Serial.println(analogRead(Red));
//  Done = analogRead(White);
 
 Serial.println(digitalRead(7));
 if (LOW == digitalRead(7)) {
   DigitShield.setValue(00.00);
   delay(1000);
 }
 
 Serial.println(digitalRead(0));
 
if (LOW == digitalRead(0)) {
     DigitShield.setValue(99.99);
     delay(1000);
 }
 
if (LOW == digitalRead(1)) {
   d = 1;
 }
 
  DigitShield.setValue(counter);
  counter = counter - .01;
  delay(d);
  if (counter >= 100) {
    counter = 0.0;
  }
}
