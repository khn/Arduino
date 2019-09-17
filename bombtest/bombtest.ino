

#include <DigitShield.h>

int BigRedButton = 0;
int Buzzer = 6;
int BigRedLight = 10;
int MainSwitch = 7;
int SwitchedOn = 0;
long interval = 1000;  


float counter = 10;
int d = 10;


void setup() {
  DigitShield.begin();
  DigitShield.setPrecision(2);
  pinMode(BigRedButton, INPUT);
  digitalWrite(BigRedButton, HIGH);
  pinMode(MainSwitch, INPUT);
  digitalWrite(MainSwitch, HIGH);
  pinMode(Buzzer, OUTPUT);
  pinMode(BigRedLight, OUTPUT);
}

void loop() {
  
  while(digitalRead(MainSwitch) == LOW) {
  
    if (0 == SwitchedOn ) {
     // analogWrite(Buzzer, 200);
       tone(Buzzer, 2000);
      delay(200);
      noTone(Buzzer);
      delay(5);
       tone(Buzzer, 2200);
     // analogWrite(Buzzer, 70);
      delay(200);
      noTone(Buzzer);
     //digitalWrite(Buzzer, LOW);
      SwitchedOn = 1;
    }

  
    DigitShield.setBlank(false);
    DigitShield.setValue(counter);
  
   if (digitalRead(BigRedButton) == LOW) {  
    while(counter > 0) {
     counter = counter - 0.01;
      DigitShield.setValue(counter);
      if(counter == 9 || counter == 8) {
       tone(Buzzer, 200, 100); 
      }
      delay(1);
    }
    counter = 0.00;
    DigitShield.setValue(counter);
//    tone(Buzzer, 700);
    delay(1000);
    noTone(Buzzer);
    }  
  }
  noTone(Buzzer);
  DigitShield.setBlank(true);
  counter = 10;
  SwitchedOn = 0;
}


unsigned long previousMillis = millis();
unsigned long currentMillis = millis();
 if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;   
