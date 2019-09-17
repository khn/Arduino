#include <Adafruit_NeoPixel.h>
#include <RGBledstruct.h>



#define PIN 6

int sensorPin = A2;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
// struct stRGBLED {int nPos; int nRed; int nGreen; int nBlue; int nBrightness;};
int nDelay = 0;
int nFadeValue = 255;  
boolean  bUp = false;
stRGBLED topLED = {0,0,0,0,0};
stRGBLED lowLED = {1,0,255,0,0};
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  int iVal;
  sensorValue = analogRead(sensorPin); 
  iVal = map(sensorValue, 0, 1023, 0, 255);
 // Serial.println(iVal);
  ChangeLight(&topLED, iVal);
  ChangeLight(&lowLED, iVal);
  // strip.setPixelColor(0, strip.Color(topLED.nRed,topLED.nGreen,topLED.nBlue));
  // strip.setPixelColor(1, strip.Color(lowLED.nRed,lowLED.nGreen,lowLED.nBlue));
  // strip.setPixelColor(1, strip.Color(255,0,0));
  //  Serial.print("Red = " );                       
  //  Serial.print(lowLED.nRed);      
  //  Serial.print("\t GREEN = ");  
  //  Serial.print(lowLED.nGreen); 
  //  Serial.print("\t BLUE = ");     
  //  Serial.println(lowLED.nBlue);
  //  strip.show

  if (bUp)
  {
    nFadeValue = nFadeValue+1;
    if (255 < nFadeValue)
    {
      nFadeValue = 255;
      bUp = false; 
    }
  } 
  else {
    nFadeValue = nFadeValue-1;
    if (150 > nFadeValue)
    {
      bUp = true; 
    }
  }
  Serial.println(nFadeValue);
  strip.setBrightness(nFadeValue);
  strip.show();
  delay(10);
}

void ChangeLight (stRGBLED *led, int nNew)
{ 
  int r,g,b = 0;
  int nAdjust = 0;

  if (nNew > 200)
  {
    // red
    r = 255;
    g = 0;
    b = 0;
    nDelay = 0;
    // Serial.println("RED");
  } 
  else if (nNew < 100)
  {
    // Green
    r = 0;
    g = 255;
    b = 0;
    nDelay = 0;
    //  Serial.println("GREEN");
  } 
  else {
    // Blue
    r = 0;
    g = 0;
    b = 255;
    nDelay = 0;
    // Serial.println("BLUE");
  }

  while ( 1 == led->nPos &&
    (r != led->nRed ||
    g != led->nGreen ||
    b != led->nBlue))
  {        
    nAdjust = AdjustColor(r, led->nRed);
    led->nRed = nAdjust;
    nAdjust = AdjustColor(g, led->nGreen);
    led->nGreen = nAdjust;
    nAdjust = AdjustColor(b, led->nBlue);
    led->nBlue = nAdjust;

    strip.setPixelColor(led->nPos, strip.Color(led->nRed,led->nGreen,led->nBlue));
    strip.show();
    delay(10);
  }

  while ( 0 == led->nPos &&
    (r != led->nRed ||
    g != led->nGreen ||
    b != led->nBlue))
  {
    nAdjust = AdjustColor(r, led->nRed);
    led->nRed = nAdjust;
    nAdjust = AdjustColor(g, led->nGreen);
    led->nGreen = nAdjust;
    nAdjust = AdjustColor(b, led->nBlue);
    led->nBlue = nAdjust;

    strip.setPixelColor(led->nPos, strip.Color(led->nRed,led->nGreen,led->nBlue));
    strip.show();
    delay(10);
  }

  // led->nRed = r;
  // led->nGreen = g;
  // led->nBlue = b;

}

int AdjustColor(int nTarget, int nIncoming)
{
  int nStep = 1;
  int nNew = 0;

  if (nIncoming > nTarget)
  {
    nNew = nIncoming-nStep; 
  } 
  else if (nIncoming < nTarget)
  {
    nNew = nIncoming+nStep; 
  } 
  else 
  {
    nNew = nIncoming;
  }

  // Serial.print("nNew ");
  // Serial.println(nNew);
  if (nNew > 255)
  {
    nNew = 255;
  } 
  else if (nNew < 1)
  {
    nNew = 0; 
  }
  return nNew; 
}

