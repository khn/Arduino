#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


// Used for I2C or SPI
#define OLED_RESET 9

// Pin used for main overhead light
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

// I2C
Adafruit_SSD1305 display(OLED_RESET);


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int motor = 8;
int bottom = A1;
int top = A2;
int RedButton = 3;
int sound = 4;
int soundDelay = 200;
boolean bDisplayUpdate = true;


void setup() {
   Serial.begin(9600);
    pixels.begin(); // This initializes the NeoPixel library.
    display.begin();
    pinMode(motor, OUTPUT);
    pinMode(sound, OUTPUT);
    pinMode(bottom, INPUT);
    pinMode(top, INPUT);
    pinMode(RedButton, INPUT_PULLUP);
}

void loop() {
 
  while (HIGH == digitalRead(RedButton)) {
    if(!bDisplayUpdate) {
       PixleOff();
       // PixleOn();
       waiting();
       bDisplayUpdate = true; 
    }
    delay(20);
  }
  
  overheadOn();
  
  digitalWrite(sound, HIGH);
  delay(soundDelay);
  digitalWrite(sound, LOW);

  delay(2000); 
  intro();
  
  while(HIGH == digitalRead(top)) {
      digitalWrite(motor, HIGH);
     delay(20);
  }
  digitalWrite(motor, LOW);
  delay(500);
  
  digitalWrite(sound, HIGH);
  delay(soundDelay);
  digitalWrite(sound, LOW);


  fortune();
  display.clearDisplay();
  display.display();
  while(HIGH == digitalRead(bottom)) {
     digitalWrite(motor, HIGH);
     delay(20);
  }
  digitalWrite(motor, LOW);
    
  digitalWrite(sound, HIGH);
  delay(soundDelay);
  digitalWrite(sound, LOW);

  overheadOff();
  bDisplayUpdate = false;
  delay(3000); 
}
  
// All pixels off (for slightly cleaner code.)
void PixleOff(){
 for(int i=0;i<NUMPIXELS;i++){

    pixels.setPixelColor(i, pixels.Color(0,0,0)); 
  }
 pixels.show();

}

// On with a slightly warmer/yellow color
void PixleOn() {

  for(int i=0;i<NUMPIXELS;i++){

    pixels.setPixelColor(i, pixels.Color(255,255,102));     
  }
  pixels.show(); 
}

// I see this all over the web, but for the life of me I can't find the original. 
void rgbFadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
  for(uint8_t b = 50; b <255; b++) {
     for(uint8_t i=0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, red * b/255, green * b/255, blue * b/255);
     }
     pixels.show();
     delay(wait);
  }
}

// Fun flickery effect. Like turning on an old fluorescent light.
void overheadOn() {
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
}

// Turning light back off.

void overheadOff() {
  PixleOff();
     delay(350); 
  PixleOn();
     delay(100); 
  PixleOff();
     delay(60); 
  PixleOn();
     delay(85); 
  PixleOff();
     delay(100); 
  PixleOn();
     delay(75); 
  PixleOff();
     delay(250); 
  PixleOn();
     delay(75); 
  rgbFadeInAndOut(0,0,0,5);
}

void waiting() {
     display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    display.println(F("Get Your\nFortune."));
    display.display();
    delay(20);
}

void intro() {
  display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    //display.println("I will peer into\nthe ether\nand find your\nfortune.");
    display.println(F("I will peer into\nthe ether\nand find your\nfortune."));
    display.display();
    delay(2000);
}

void fortune() {
  display.clearDisplay();  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

   // display.println("Your face will melt\noff your skull.\nNuns will find it\nfunny.");
    display.println(F("Your face will melt\noff your skull.\nNuns will find it\nfunny."));
    display.display();
    delay(3000);
}



