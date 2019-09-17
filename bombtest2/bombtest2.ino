#include <DigitShield.h>

int BigRedButton = 0;
int BigRedLight = 10;
int MainSwitch = 7;
int SwitchedOn = 0;
int nCounter = 0;
int nLight = 0;
int nDone = 0;


float counter = 10;
int d = 10;


void setup() {
  Serial.begin(9600);
  DigitShield.begin();
  DigitShield.setPrecision(2);
  pinMode(BigRedButton, INPUT);
  digitalWrite(BigRedButton, HIGH);
  pinMode(MainSwitch, INPUT);
  digitalWrite(MainSwitch, HIGH);
  pinMode(BigRedLight, OUTPUT);
}

void loop() {

  while(digitalRead(MainSwitch) == LOW) {

    if (0 == SwitchedOn ) {
      SwitchedOn = 1;
      nLight = 1;
      digitalWrite(BigRedLight, nLight);
      nDone = 0;
      nCounter = 0;
    }

    DigitShield.setBlank(false);
    DigitShield.setValue(counter);

    if (digitalRead(BigRedButton) == LOW) {  
      while(counter > 0) {
        counter = counter - 0.01;
        DigitShield.setValue(counter);
        delay(10);
      }
      counter = 0.00;
      DigitShield.setValue(counter);
      nDone = 1;
      delay(1000);
    }  
    delay(10);
    nCounter += 10; 
    Serial.println(nCounter); 

    if(1000 == nCounter && 1 != nDone)  
    {
      if (nLight == 1)
      {
        nLight = 0; 
      } 
      else { 
        nLight = 1;
      } 
      digitalWrite(BigRedLight, nLight);
      nCounter = 0;
    }

      Serial.println(nDone); 
  }
  DigitShield.setBlank(true);
  counter = 10;
  SwitchedOn = 0;
  nLight = 0; 
  digitalWrite(BigRedLight, nLight);
}


