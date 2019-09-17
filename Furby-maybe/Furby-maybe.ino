#include <NewSoftSerial.h>
#include <string.h>
#define HTTP_HEADER "HTTP/1.0 200 OKnServer: arduinonContent-Type: text/htmlnn"
#define IP_ADDRESS "192.168.1.4"
// Furby Pinning
// Analog inputs:
#define tummy 0
#define back 2
#define light 1
#define light_dig 3
#define upside_down 4
#define tilt 5
// digital pins
#define feed 7
#define motor_forward 6
#define motor_backward 5
#define cam_home 4
// external interrupts:
#define gear_rotation 3
#define sound_in 2
// Xport Pinning
#define XPORT_CP2 11 // on shield labeled as CP2, in fact is CP1 in config thingy..
#define XPORT_RXPIN 12
#define XPORT_TXPIN 13

char linebuffer[256];
char c;
int analog[6];
int requestNumber = 0;
NewSoftSerial mySerial = NewSoftSerial(XPORT_TXPIN, XPORT_RXPIN);
volatile int encoder_count;
void setup()
{
  pinMode(cam_home, INPUT);
  digitalWrite(cam_home, HIGH); //pullup
  pinMode(gear_rotation, INPUT);
  pinMode(motor_forward, OUTPUT);
  pinMode(motor_backward, OUTPUT);

  attachInterrupt(1, encoder, RISING);
  //attachInterrupt(1, sound, FALLING);
  Serial.begin(57600);
  pinMode(XPORT_CP2, OUTPUT);
  Serial.println("serial port ready");
  mySerial.begin(19200);
  Serial.println("ethernet response ready");
  digitalWrite(XPORT_CP2, HIGH);
  for (int n = 14; n < 20; n++) {
    digitalWrite(n, HIGH); // pullups on analog inputs
  }
  reset(); // set furby in start position
}
void loop()
{
  checkAnalogIns();
  if (requested()) {
    respond();
  }
}

void encoder()
{
  if (digitalRead(motor_forward) == HIGH) encoder_count++;
  if (digitalRead(motor_backward) == HIGH) encoder_count–;
  if (digitalRead(cam_home) == LOW) encoder_count = 0; // reset
}

void reset()
{
  digitalWrite(motor_backward, HIGH);
  while (digitalRead(cam_home) == HIGH) {};
  digitalWrite(motor_backward, LOW);
}

void move(int setpoint)
{
  if (setpoint == 0) {
    reset();
  }
  int error = setpoint – encoder_count;
  if (error > 0) digitalWrite(motor_forward, HIGH);
  else if (error < 0) digitalWrite(motor_backward, HIGH);

  while (abs(error) > 0) {
    error = setpoint – encoder_count;
  }
  digitalWrite(motor_forward, LOW);
  digitalWrite(motor_backward, LOW);
}

uint8_t serialavail_timeout(int timeout) { // in ms
  while (timeout) {
    if (mySerial.available()) {
      return 1;
    }
    timeout -= 1;
    delay(1);
  }
  return 0;
}

uint8_t readline_timeout(int timeout) {
  uint8_t idx = 0;
  char c;
  while (serialavail_timeout(timeout)) {
    c = mySerial.read();
    // Serial.print(c);
    linebuffer[idx++] = c;
    if ((c == ‘n’) || (idx == 255)) {
      linebuffer[idx] = 0; return idx;
    }
  }
  linebuffer[idx] = 0;
  return idx;
}

int requested(void) {
  uint8_t ret;
  char *found = 0, *start = 0, *end = 0;
  while (1) {
    ret = readline_timeout(200);
    found = strstr(linebuffer, "GET /");
    if (((int)found) != 0) {
      if (strstr(linebuffer, "POS=START") != 0) move(0);
      if (strstr(linebuffer, "POS=MID") != 0) move(30);
      return 1;
    }
    return 0;
  }
}

void XPort_flush(int timeout) {
  while (serialavail_timeout(timeout)) {
    mySerial.read();
  }
}

void checkAnalogIns() {
  for (int n = 0; n < 6 ; n++)
  {
    analog[n] = analogRead(n);
  }

}

void respond() {
  XPort_flush(50);
  int color = analog[3] / 4;
  mySerial.print(HTTP_HEADER);
  mySerial.print("<html><body bgcolor="");//<meta http-equiv="refresh" content="200">
                 mySerial.print(color, HEX);
                 mySerial.print(color, HEX);
                 mySerial.print(color, HEX);
                 mySerial.print("" text="");
                 mySerial.print(0xff-color, HEX);
                 mySerial.print(0xff-color, HEX);
                 mySerial.print(0xff-color, HEX);
                 mySerial.print(""><h1>FURBYSERVE</h1><FORM action="http://");
                 mySerial.print(IP_ADDRESS);
                 mySerial.print(":10001/furby.html" method = "get" > ");
                                mySerial.print("<INPUT type = "radio" name = "POS" value = "START"> START<BR>");
                                    mySerial.print("<INPUT type = "radio" name = "POS" value = "MID"> MID<BR>");
                                        mySerial.print("<INPUT type = "submit" value = "S"> < / FORM > ");
                                            mySerial.print("<h3>My analog - in values are: < / h3 > <ul>");

                                            for (int i = 0; i < 6; i++){
                                            mySerial.print("<li><b>");
                                            mySerial.print(i);
                                            mySerial.print(": < / b > &nbsp; ");
                                mySerial.print(analog[i]);
                                mySerial.print(" < / li > ");
                                analog[1] = 0;
                              }

                                mySerial.print(" < / ul > < / body > < / html > ");
                                XPort_disconnect();

                                Serial.print("Requested! No. ");
                                Serial.println(requestNumber++);

                              }

                                void XPort_disconnect(){
                                digitalWrite(XPORT_CP2, LOW);
                                delay(20);
                                digitalWrite(XPORT_CP2, HIGH);
                              }
