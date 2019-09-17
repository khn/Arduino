 int First = 9;
int Second = 10;
int Third = 11;
int nSteps = 3;
int Sound = 6;
int nDelayBase = 15;
int nDelayStep1 = nDelayBase + 15;
int nDelayStep2 = nDelayBase + 30;
int nLightTime = 1000;
int nOffTime = 1000;
int XAxis = 1;

void setup(){
  Serial.begin(9600); 
  pinMode(First, OUTPUT);
  pinMode(Second, OUTPUT);
  pinMode(Third, OUTPUT);
  pinMode(Sound, OUTPUT);
  pinMode(XAxis, INPUT);
}

void loop() {
  int xValue = analogRead(XAxis);
      Serial.println(analogRead(XAxis));
     if ( 800 <+ analogRead(XAxis)) {
      Lightning();
      }
}                                 

void Lightning() {
  
  //Sound on )
  digitalWrite(Sound, HIGH);
  
   // light up  
  for (int i = 0; i < nSteps; i++) {
    digitalWrite(First, HIGH);
    delay(nDelayBase); 
    digitalWrite(First, LOW);
    delay(nDelayBase); 
  }

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(First, HIGH);
    delay(nDelayStep1); 
    digitalWrite(First, LOW);
    delay(nDelayBase); 
  }

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(First, HIGH);
    delay(nDelayBase); 
    digitalWrite(First, LOW);
    delay(nDelayBase); 
    digitalWrite(First, HIGH);     
    digitalWrite(Second, HIGH);
    delay(nDelayBase); 
    digitalWrite(First, LOW);
    digitalWrite(Second, LOW);
    delay(nDelayBase);       
  }
  digitalWrite(First, HIGH);

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(Second, HIGH);
    delay(nDelayStep1); 
    digitalWrite(Second, LOW);
    delay(nDelayBase); 
  }

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(Second, HIGH);
    delay(nDelayBase); 
    digitalWrite(Second, LOW);
    delay(nDelayBase); 
    digitalWrite(Second, HIGH);     
    digitalWrite(Third, HIGH);
    delay(nDelayBase); 
    digitalWrite(Second, LOW);
    digitalWrite(Third, LOW);
    delay(nDelayBase);       
  }
  digitalWrite(Second, HIGH);

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(Third, HIGH);
    delay(nDelayStep1); 
    digitalWrite(Third, LOW);
    delay(nDelayBase); 
  }

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(Third, HIGH);
    delay(nDelayBase); 
    digitalWrite(Third, LOW);
    delay(nDelayBase); 
  }
  digitalWrite(Third, HIGH);


  delay(nLightTime);

  //Shut down
  for (int i = 0; i < nSteps; i++) {
    digitalWrite(First, LOW);
    delay(nDelayBase); 
    digitalWrite(First, HIGH);
    delay(nDelayBase); 
  }

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(First, LOW);
    delay(nDelayStep1); 
    digitalWrite(First, HIGH);
    delay(nDelayBase); 
  }

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(First, LOW);
    delay(nDelayBase); 
    digitalWrite(First, HIGH);
    delay(nDelayBase); 
    digitalWrite(First, LOW);     
    digitalWrite(Second, LOW);
    delay(nDelayBase); 
    digitalWrite(First, HIGH);
    digitalWrite(Second, HIGH);
    delay(nDelayBase);       
  }
  digitalWrite(First, LOW);

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(Second, LOW);
    delay(nDelayStep1); 
    digitalWrite(Second, HIGH);
    delay(nDelayBase); 
  }

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(Second, LOW);
    delay(nDelayBase); 
    digitalWrite(Second, HIGH);
    delay(nDelayBase); 
    digitalWrite(Second, LOW);     
    digitalWrite(Third, LOW);
    delay(nDelayBase); 
    digitalWrite(Second, HIGH);
    digitalWrite(Third, HIGH);
    delay(nDelayBase);       
  }
  digitalWrite(Second, LOW);

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(Third, LOW);
    delay(nDelayStep1); 
    digitalWrite(Third, HIGH);
    delay(nDelayBase); 
  }

  for (int i = 0; i < nSteps; i++) {
    digitalWrite(Third, LOW);
    delay(nDelayStep2); 
    digitalWrite(Third, HIGH);
    delay(nDelayBase); 
  }
  digitalWrite(Third, LOW);
  //Sound off
  digitalWrite(Sound, LOW);
  
}
