
int nTarget = 0;
int nCurrent = 0;
int stAdjustment[3] = {
  0,0,0};
int stPulse[3] = {
  0,0,0};
int stRGBValue[3] = {
  0,0,0};
int nColorChangeSpeed = 0;
boolean bHeadingUp = TRUE;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  nTarget = map(analogRead(A0), 0,1023, 1,20 );
  Serial.println(analogRead(A0));




  nColorChangeSpeed = (1 /(abs(nTarget - nCurrent)) * 100);



  if (nCurrent != nTarget) {
        if (nCurrent > nTarget) {
          bHeadingUp = FALSE;
        } else {
         TRUE; 
        }
    
    GetAdjustmentValue(nCurrent, stAdjustment);
    
    if (!bHeadingUp) {
      stAdjustment[0] *= -1;
      stAdjustment[1] *= -1;
      stAdjustment[2] *= -1;
    }
  }



  delay(1);        // delay in between reads for stability
}

/* Gets the values to adjust each pin on an RGB LED to switch from one color to the next
 Set up so that it doesn't matter which way you need to adjust. If you are trying to change the currnet value to the next lower value, just multply the result by x 1*/
int GetAdjustmentValue(int nCurrentValue, int stAdjust[3]) {
//should change to a mathmatical formula based on a set value of colors. (So that the colors can be set as constants at the top and the adjustments are calculated automatically)
  switch (nCurrentValue) {
  case 1:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  case 2:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  case 3:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  case 4:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  case 5:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  case 6:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  case 7:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  case 8:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  case 9:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  case 10:
    stAdjust[0] = 10; //Red
    stAdjust[1] = 10; //Green
    stAdjust[2] = 10; //Blue
    break;
  }
  return 0;
}




