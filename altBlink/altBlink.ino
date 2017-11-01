

#define btn 2
volatile byte fastLED=5;
volatile byte slowLED=6;

void setup() {
  // put your setup code here, to run once:
  pinMode(fastLED,OUTPUT);
  pinMode(slowLED, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  attachInterrupt(0,flipLED_ISR, CHANGE);
  
}



void flipLED_ISR()
{
  byte temp = slowLED;
  slowLED=fastLED;
  fastLED =temp;
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(fastLED,HIGH);
  digitalWrite(slowLED,HIGH);
  
  delay(240);
  digitalWrite(fastLED,LOW);
  
  
  delay(240);
  digitalWrite(slowLED,LOW);
  digitalWrite(fastLED,HIGH);
 
  delay(240);
  digitalWrite(fastLED,LOW);
  digitalWrite(slowLED,LOW);
 
  
  delay(240);
 
  
}
