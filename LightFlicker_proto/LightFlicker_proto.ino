// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  /*
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif */
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

PixleOff();
   delay(1000); 
PixleOn();
   delay(75); 
PixleOff();
   delay(250); 
PixleOn();
   delay(75); 
PixleOff();
   delay(100); 
PixleOn();
   delay(85); 
PixleOff();
   delay(60); 
PixleOn();
   delay(100); 
PixleOff();
   delay(350); 
  rgbFadeInAndOut(255,255,102,5);
// for(int q=50;q<250;q++){
//
// for(int i=0;i<NUMPIXELS;i++){
//int nRed =
//    pixels.setPixelColor(i, pixels.Color(q,q,q)); 
//  }
//  
// pixels.show();
//  
//   delay(5); 
//  }


   delay(10000);   
}

void PixleOff(){
 for(int i=0;i<NUMPIXELS;i++){

    pixels.setPixelColor(i, pixels.Color(0,0,0)); 
  }
 pixels.show();

}

void PixleOn() {

  for(int i=0;i<NUMPIXELS;i++){

    pixels.setPixelColor(i, pixels.Color(255,255,102)); // Moderately bright green color.    
  }
  pixels.show(); 

  }


void rgbFadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
  for(uint8_t b = 50; b <255; b++) {
     for(uint8_t i=0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, red * b/255, green * b/255, blue * b/255);
     }
     pixels.show();
     delay(wait);
  }
}
