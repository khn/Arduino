#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>
#include <Adafruit_NeoPixel.h>
#include <TrueRandom.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
// #include <Fortunes.h>

// Used for I2C or SPI
#define OLED_RESET     9

// Pin used for main overhead light
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

// Main motor pin (via MOSFET)
#define MOTOR          8

// Lowwer hall effect sensor. Goes to ground when South magnet present
#define BOTTOMHALL A1

// Upper hall effect sensor. Goes to ground when South  magnet present
#define TOPHALL    A2

// Activates on LOW.
#define REDBUTTON      3

// Go HIGH when we want sound to play
#define SOUND          4

// I2C
Adafruit_SSD1305 display(OLED_RESET);

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int nSoundDelay = 200; // Indicates how long the SOUND pin will be held high to play.
int nFortuneDelay = 2000; // How long the fortune will remain on the OLED.
int nIntroTimer = 0; // used to cycle through text on the OLED while waiting for the button push.
int nIntroDisply = 0; // Used to store which intro text we're currently displaying.

void setup() {
  // Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.

  // Set display
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("The Baby\nSees You."));
  display.begin();

  // Set pin modes
  pinMode(MOTOR, OUTPUT);
  pinMode(SOUND, OUTPUT);
  pinMode(BOTTOMHALL, INPUT);
  pinMode(TOPHALL, INPUT);
  pinMode(REDBUTTON, INPUT_PULLUP);
  randomSeed(analogRead(A5));
}

void loop() {

  // If timer has been running for under 3 seconds and is NOT the first intro text option
  if (nIntroTimer <= 3000 && 1 != nIntroDisply) {

    // Then set to first text option.
    waiting(1);
    // and set variable to track
    nIntroDisply = 1;
  }

  // If timer has been running for more than 3 seconds and is NOT the second intro text option
  if (nIntroTimer < 6000 && nIntroTimer > 3000 && 2 != nIntroDisply) {
    // Then set to second text option.

    waiting(2);
    // and set variable to track
    nIntroDisply = 2;
  }

  // If timer has been running for more than 6 seconds and is NOT the third intro text option
  if (nIntroTimer > 6000 && 3 != nIntroDisply) {
    // Then set to third text option.
    waiting(3);
    // and set variable to track
    nIntroDisply = 3;
  }
  nIntroTimer += 20;
  delay(20);

  if (LOW == digitalRead(REDBUTTON)) {
    //Button push
    ButtonPushed();
    // Resset counters
    nIntroTimer = 0;
    nIntroDisply = 0;
  }

  // If timer greater than 9 seconds
  if (nIntroTimer > 9000) {
    //Reset timer
    nIntroTimer = 0;
  }
}

void ButtonPushed() {
  overheadOn();

  // intro();
  // delay(1500);

  //  digitalWrite(SOUND, HIGH);
  //  delay(nSoundDelay);
  //  digitalWrite(SOUND, LOW);

  //delay(500);

  //  while (HIGH == digitalRead(TOPHALL)) {
  //    digitalWrite(MOTOR, HIGH);
  //    delay(20);
  //  }
  //  digitalWrite(MOTOR, LOW);
  //  delay(500);
  //
  //  digitalWrite(SOUND, HIGH);
  //  delay(nSoundDelay);
  //  digitalWrite(SOUND, LOW);
  //  digitalWrite(MOTOR, LOW);

  //  delay(1000);
  fortune();
  delay(nFortuneDelay);
  // Reset
  // display.clearDisplay();
  // display.display();
  //  while (HIGH == digitalRead(BOTTOMHALL)) {
  //    digitalWrite(MOTOR, HIGH);
  //    delay(20);
  //  }
  //  digitalWrite(MOTOR, LOW);
  //
  //  digitalWrite(SOUND, HIGH);
  //  delay(nSoundDelay);
  //  digitalWrite(SOUND, LOW);

  overheadOff();
  delay(1000);

}


// All pixels off (for slightly cleaner code.)
void PixleOff() {
  for (int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

// On with a slightly warmer/yellow color
void PixleOn() {

  for (int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(255, 255, 102));
  }
  pixels.show();
}

// I see this all over the web, but for the life of me I can't find the original.
void rgbFadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
  for (uint8_t b = 50; b < 255; b++) {
    for (uint8_t i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
    }
    pixels.show();
    delay(wait);
  }
}

// Fun flickery effect. Like turning on an old fluorescent light.
void overheadOn() {
  //  PixleOn();
  //  delay(75);
  //  PixleOff();
  //  delay(250);
  //  PixleOn();
  //  delay(75);
  //  PixleOff();
  //  delay(100);
  //  PixleOn();
  //  delay(85);
  //  PixleOff();
  //  delay(60);
  //  PixleOn();
  //  delay(100);
  //  PixleOff();
  //  delay(350);
  rgbFadeInAndOut(255, 255, 102, 5);
}

// Turning light back off.
void overheadOff() {
  int red = 255;
  int green = 255;
  int blue = 102;
  int wait = 1;

for (uint8_t b = 130; b > 0; b--) {
    for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
  }
  pixels.show();
    delay(wait);
}

//for (uint8_t b = 50; b > 0; b--) {
//    for (int i = 0; i < NUMPIXELS; i++) {
//    pixels.setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
//  }
//  pixels.show();
//    delay(5);
//}
}

void waiting(int nMessage) {

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  if (nMessage == 1) {
    display.setTextSize(2);
    display.println(F("Get Your\nFortune."));
  }
  else if (nMessage == 2) {
    display.setTextSize(1);
    display.println(F("Push the button and\nrecieve a fortune.\nThe wonders of the\nfuture await you!"));
  }
  else if (nMessage == 3) {
    display.setTextSize(1);
    display.println(F("The mysteries\nof the Universe\ncan be yours!"));
  }
  else {
    display.setTextSize(2);
    display.println(F("ERROR!"));
  }
  display.display();
}

void intro() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println(F("I will peer into\nthe ether\nand find your\nfortune."));
  display.display();
}

/*  I had hoped to make this a little more elegant,
    but memory constraints mean that I need to use the F() function to keep the
    fortunes from taking up all the Global variable space. This isn't too bad though. -KHN
*/
void fortune() {
  int nRandomNum;
  // 2-29 because most people don't think clock dick is funny
  nRandomNum = TrueRandom.random(2, 29);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // randomSeed(analogRead(A5));
  switch (nRandomNum) { // one plus the number of fortunes here. (Don't forget it starts at 0)
    case 0:
      display.println(F("You're Pregnant."));
      break;
    case 1:
      display.println(F("Clock dick. There is\nclock dick in your\nfuture."));
      break;
    case 2:
      display.println(F("You will be eaten by\nwild wolves."));
      break;
    case 3:
      display.println(F("You will go on a long\njourney, and become\nhopelessly lost.\nForever."));
      break;
    case 4:
      display.println(F("I dare not say, but I\nhope you like spiders\nin your mouth."));
      break;
    case 5:
      display.println(F("You will spend an\nunusually high amount\nof your life waiting for toast."));
      break;
    case 6:
      display.println(F("Blood Blood Blood\nBlood Blood Blood\nBlood Blood Blood\nSO MUCH BLOOD!"));
      break;
    case 7:
      display.println(F("Study the effects of\ngangrene.\nIt is knowledge you\nwill soon need."));
      break;
    case 8:
      display.println(F("Your body will\nprovide a house full\nof cats an excellent\nChristmas dinner."));
      break;
    case 9:
      display.println(F("You'll be famous...\nwhen they name that\nhorrible consuming\ndisease after you."));
      break;
    case 10:
      display.println(F("Treat your money like\nyou would your hands,\nbecause you're\ngoing to lose both."));
      break;
    case 11:
      display.println(F("Having your eyes\neaten out of your\nskull is unpleasant.\nThis you will know."));
      break;
    case 12:
      display.println(F("You will find $4.52.\nYou will have 23\nhours to spend it."));
      break;
    case 13:
      display.println(F("If you were wise,\nyou'd get used to\ndrinking urine now."));
      break;
    case 14:
      display.println(F("An optimist would say\nthat next week you\nwill be half FULL\nof blood."));
      break;
    case 15:
      display.println(F("It will take years,\nbut they WILL one day\nfind what's left\nof your body."));
      break;
    case 16:
      display.println(F("Beautiful flowers\nwill bloom on your\nshallow grave."));
      break;
    case 17:
      display.println(F("The rats will eat\nyour toes first."));
      break;
    case 18:
      display.println(F("Bystanders will\ndiscover too late\nyou are not waving,\nbut drowning."));
      break;
    case 19:
      // display.println(F("Live every day as if\nit is your last until\nyou die at 8:39 a. m."));
      display.println(F("Live every day as if\nyou die will\nat 8:39 a. m.\nTrust me."));
      break;
    case 20:
      display.println(F("You won't lose your\nhair. I'll keep all\nfallen strands."));
      break;
    case 21:
      display.println(F("The itch you feel\nwill only get worse\nuntil you find the\nspider. FIND IT!"));
      break;
    case 22:
      display.println(F("Congratulations!\nYou will lose 10 lb\nRelated:\nYour head weighs 10lb"));
      break;
    case 23:
      display.println(F("You won't ever drive\nin traffic again b/c\nyou will become blind"));
      break;
    case 24:
      display.println(F("You will become more\nboring. (Yes it is\npossible.)"));
      break;
    case 25:
      display.println(F("A fairy attack will\nresult in untreatable\nglitter herpies."));
      break;
    case 26:
      display.println(F("The next thing you\neat will give you\nfood poisoning."));
      break;
    case 27:
      display.println(F("You will meet someone\nwho will have no\neffect on your life."));
      break;
    case 28:
      display.println(F("You will spend hours,\nHOURS at the DMV.\nMaybe days"));
      break;
  }
  display.display();
}


