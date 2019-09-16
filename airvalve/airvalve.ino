
// Neopixil setup
#include <Adafruit_NeoPixel.h>
#include <ledstruct.h>

// set pin numbers:
#define valveOne 12
#define valveTwo 8
#define valveThree 7
#define valveFour 4
#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

int nTimer = 0;

// Create variables for the four lights.
// prototype of structure
// struct stLED {int nPos; int nBrightness;};
stLED FirstLED = {
  0,0};
stLED SecondLED = {
  1,0};
stLED ThirdLED = {
  2,0};
stLED FourthLED = {
  3,0};

int nCurrentPod = 0;
int nValve = 0;

// variables will change:

void setup() {
  // Set the pin modes`
  pinMode(valveOne, OUTPUT);      
  pinMode(valveTwo, OUTPUT);      
  pinMode(valveThree, OUTPUT);      
  pinMode(valveFour, OUTPUT);      
  strip.begin(); // Start pixels
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600); 
}

void loop(){
  // Choose the next pod to enflate and enlighten
  nCurrentPod = PodChooser(nCurrentPod);
  // reset counter
  nTimer = 0;

  switch (nCurrentPod) {
  case 1:
    nValve = valveOne;
    break;
  case 2:
    nValve = valveTwo;
    break;
  case 3:
    nValve = valveThree;
    break;
  case 4:
    nValve = valveFour;
    break;
  }
  
  //Open Valve
  digitalWrite(nValve, HIGH);
  
  while (nTimer < 3500) {
    //Brighten or dim each light
    ChangeLight(nCurrentPod, &FirstLED);
    ChangeLight(nCurrentPod, &SecondLED);
    ChangeLight(nCurrentPod, &ThirdLED);  
    ChangeLight(nCurrentPod, &FourthLED);
    Serial.print("Pod = " );                       
    Serial.print(nCurrentPod);      
    Serial.print("\t Time = ");     
    Serial.println(nTimer);
    nTimer = nTimer + 100  ;
    delay(100);
  }
  /* Close Valve */
  digitalWrite(nValve, LOW);
}

void ChangeLight (int nPod, stLED *led)
{
  if(led->nPos == nPod - 1 &&
    led->nBrightness < 70){
    led->nBrightness = led->nBrightness + 2;
  } 
  else {
    if (led->nBrightness > 0) {
      led->nBrightness--;
    }
  }

  Serial.print("led = " );                       
  Serial.print(led->nPos);      
  Serial.print("\t Brigthnes = ");     
  Serial.println(led->nBrightness);
  strip.setPixelColor(led->nPos, strip.Color(0, led->nBrightness, 0));
  strip.show();
}


int PodChooser(int nOldPod) 
{
  int nNewPod = 0; // Reset nNewPod to a nonValid Pod number

  do { // Run a new random number at least once
    nNewPod = random(1,5);
  } 
  while(nNewPod == nOldPod); // Repeate until we have a new number

  return nNewPod; 
}







