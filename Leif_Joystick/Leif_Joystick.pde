#define btnTrigger 3;
#define btnThumb 2;
#define joystickVertical 0;
#define joystickHorizontal 1;
#define ledOne 11;
#define ledTwo 10;
#define ledThree 9;
#define rgbFour 6;
#define rgbFive 5;
#define rgbSix 3;
int ledCurrent = 6;
int nCurrentBrightness = 100;
int nVertValue = 0;
int nHorzValue = 0;

void setup(){
  Serial.begin(9600); 
  pinMode(rgbFour, OUTPUT);
  pinMode(rgbFive, OUTPUT);
  pinMode(rgbSix, OUTPUT);
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(ledCurrent, OUTPUT);
}

void loop() {
  if (0 == analogRead(btnTrigger)) {

    Serial.println(analogRead(btnTrigger));

    if(analogRead(joystickVertical) > 600) {  

      nVertValue = map(analogRead(joystickVertical), 600, 1023, 1, 10);
      Serial.print("VertValue = " );
      Serial.println(nVertValue);   
      delay(40); 
    } 
    else if (analogRead(joystickVertical) < 400 )  {

      nVertValue = map(analogRead(joystickVertical), 400, 0, -1, -10);
      Serial.print("VertValue = " );
      Serial.println(nVertValue);  
      delay(40); 
    } 
    else {
      nVertValue = 0;
      delay(40); 
    }

    //Serial.println(analogRead(joystickVertical));   


    if( 600 < analogRead(joystickHorizontal)) {
      nHorzValue = map(analogRead(joystickHorizontal), 600, 1023, 1, 10);
      Serial.print("HorzValue = " );
      Serial.println(nHorzValue);   
      nCurrentBrightness = 0;
      ledCurrent = SwitchLed(ledCurrent, nHorzValue);
      nCurrentBrightness = 255;
      while (5 < nHorzValue) {
        nHorzValue = map(analogRead(joystickHorizontal), 600, 1023, 1, 10);
        delay(30);
      } 

    } 
    else if(400 > analogRead(joystickHorizontal)){
      nHorzValue = map(analogRead(joystickHorizontal), 400, 0, -1, -10);
      Serial.print("HorzValue = " );
      Serial.println(nHorzValue);
      nCurrentBrightness = 0;   
      ledCurrent = SwitchLed(ledCurrent, nHorzValue);
      nCurrentBrightness = 255;
      while (-5 > nHorzValue) {
        nHorzValue = map(analogRead(joystickHorizontal), 400, 0, -1, -10);
        delay(30);
      }  

    } 
    else {
      nHorzValue = 0; 
    }
    Serial.print("Current LED");
    Serial.println(ledCurrent);


    if(0 == analogRead(btnThumb)) {
      digitalWrite(ledCurrent, !digitalRead(ledCurrent));
      if(HIGH == digitalRead(ledCurrent)) {
        //  If we just turned an LED on, set the brigtness.
        nCurrentBrightness = 255;
      } 
      else {
        nCurrentBrightness = 0;
      }
      Serial.println("Button Pushed");
      delay(30);

    }
    //Serial.println(analogRead(btnTrigger));


    //*********************
    // Dim or brighten LED
    // RGB LEDs have a common anode so we have to do the oposite 

    if(ledCurrent == rgbFour || ledCurrent == rgbFive || ledCurrent == rgbSix) {
      nCurrentBrightness -= nVertValue; 
    } 
    else {
      nCurrentBrightness += nVertValue; 
    }
    if (nCurrentBrightness > 255) {
      nCurrentBrightness = 255;
    } 
    else if (nCurrentBrightness < 0) {
      nCurrentBrightness = 0; 
    }

    analogWrite(ledCurrent, nCurrentBrightness);


  } else {
  nCurrentBrightness = 255;
  }
}

int SwitchLed(int ledIn, int Direction) {
  int pinOut = 0;
  const int Lights[3] = {
    3, 5, 6            };
  int nPostition = 0; //keeps track of where we are in the array.

  // Get current place in the array
  for (int i = 0; i < 2; i++) {
    if ( ledIn == Lights[i]) {
      nPostition = i; 
      Serial.print("ledIn");
      Serial.println(ledIn);      
      Serial.print("old postion");
      Serial.println(nPostition);
      delay(40); 
    }
  }

  if(Direction > 5) {
    // Switch Left 
    nPostition++;
  } 
  else {
    // Switch Right
    nPostition--;
  }
      Serial.print("New Postiton");
      Serial.println(nPostition);
      delay(40); 
  if(nPostition < 1) {
    nPostition = 3;
  } 
  else if (nPostition > 3) {
    nPostition = 1;
  }
  return(Lights[nPostition]);
}





















