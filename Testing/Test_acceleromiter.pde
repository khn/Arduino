int xAxis = 0;
int yAxis = 1;
int  zAxis = 2;
int xMax = 0;
int yMax = 0;
int zMax = 0;
int xCurrent = 0;
int yCurrent = 0;
int zCurrent = 0;
int xMin = 1023;
int yMin = 1023;
int zMin = 1023;

void setup() {
  pinMode(xAxis, INPUT);
  pinMode(yAxis, INPUT);
  pinMode(zAxis, INPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  //  int xValue = map(analogRead(xAxis), 1, 1023, 1, 30);
  //  int yValue = map(analogRead(yAxis), 1, 1023, 1, 30);
  //  int zValue = map(analogRead(zAxis), 1, 1023, 1, 30);

  xCurrent  = analogRead(xAxis);
  yCurrent = analogRead(yAxis);
  zCurrent = analogRead(zAxis);
  //  Serial.print("X = " );
  //   Serial.println(xCurrent ); 
  //   Serial.print("Y = " );
  //    Serial.println(yCurrent ); 
  //Serial.print("Z = " );
  //     Serial.println(zCurrent ); 


  if (digitalRead(7) == LOW) 
  {
    Serial.print("X Max = ");
    Serial.print(xMax);
    Serial.print(", X Min = ");
    Serial.println(xMin);
    delay(10);
    Serial.print("Y Max = ");
    Serial.print(yMax);
    Serial.print(", Y Min = ");
    Serial.println(yMin);
    delay(10);
    Serial.print("Z Max = ");
    Serial.print(zMax);
    Serial.print(", Z Min = ");
    Serial.println(zMin);
    delay(10);

    delay(1000);
    xMax = 0;
    yMax = 0;
    xMax = 0;
    xMin = 1023;
    yMin = 1023;
    zMin = 1023;
  }

  if (xCurrent > xMax) 
  {
    Serial.print("        X = " );
    Serial.println(xCurrent ); 
    xMax = xCurrent;
  }

  if (yCurrent > yMax)
  {
    Serial.print("       Y = " );
    Serial.println(yCurrent );
    yMax = yCurrent;
  }

  if (zCurrent > zMax) 
  {
    Serial.print("       Z = " );
    Serial.println(zCurrent);
    zMax = zCurrent;
  }

  if (xCurrent < xMin) 
  {
    Serial.print("Min X = " );
    Serial.println(xCurrent ); 
    xMin = xCurrent;
  }

  if (yCurrent < yMin)
  {
    Serial.print("Min Y = " );
    Serial.println(yCurrent );
    yMin = yCurrent;
  }

  if (zCurrent < zMin) 
  {
    Serial.print("Min Z = " );
    Serial.println(zCurrent);
    zMin = zCurrent;
  }

  delay(30);
} 

