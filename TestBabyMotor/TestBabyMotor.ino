int motor = 8;
int nSpeed = 105;
int speedstep = 5;
int bottom = A4;
int top = A5;

void setup() {
  // put your setup code here, to run once:
 pinMode(motor, OUTPUT);
 pinMode(bottom, INPUT);
 pinMode(top, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

while(HIGH == digitalRead(bottom)) {
 //analogWrite(motor, nSpeed);
 digitalWrite(motor, HIGH);
}
// analogWrite(motor, 0);
digitalWrite(motor, LOW);
// Serial.println("0");

 Serial.println("stop 1");
delay(3000);

 Serial.println(digitalRead(top));
while(HIGH == digitalRead(top)) {
 //analogWrite(motor, nSpeed);
 digitalWrite(motor, HIGH);
 // Serial.println(nSpeed);
}
//analogWrite(motor, 0);
digitalWrite(motor, LOW);
// Serial.println("0");
Serial.println("stop 2");
delay(3000);

}
