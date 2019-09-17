/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1305 drivers

  Pick one up today in the adafruit shop!
  ------> https://www.adafruit.com/products/2675

These displays use SPI or I2C to communicate, 3-5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


// Used for software SPI
#define OLED_CLK 13
#define OLED_MOSI 11

// Used for software or hardware SPI
#define OLED_CS 10
#define OLED_DC 8

// Used for I2C or SPI
#define OLED_RESET 9

// software SPI
Adafruit_SSD1305 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// hardware SPI
//Adafruit_SSD1305 display(OLED_DC, OLED_RESET, OLED_CS);

// I2C
Adafruit_SSD1305 display(OLED_RESET);


void setup()   {                
  Serial.begin(9600);
 
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin();
  // init done
      display.clearDisplay();
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Get Your");
    display.println("Fortune");
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer
}


void loop() {
   display.clearDisplay();
    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    display.println(F("I will peer into\nthe ether\nand find your\nfortune."));
    display.display();
    delay(2000);



  display.clearDisplay();  
  // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    display.println(F("Your face will melt\noff your skull.\nNuns will find it\nfunny."));
    display.display();
    delay(2000);


  display.clearDisplay();  
  // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    display.println(F("The quick \nbrown fox \njumps over the lazy\ndog."));
    display.display();
    delay(1000);


  display.clearDisplay();
}



