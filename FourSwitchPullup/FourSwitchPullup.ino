#define yLED 12
#define bLED 11
#define gLED 10
#define rLED 9


void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(4))
  {
    digitalWrite(rLED,LOW);
  }
  else
  {
    digitalWrite(rLED,HIGH);
  }

    if(digitalRead(5))
  {
    digitalWrite(gLED,LOW);
  }
  else
  {
    digitalWrite(gLED,HIGH);
  }

    if(digitalRead(6))
  {
    digitalWrite(bLED,LOW);
  }
  else
  {
    digitalWrite(bLED,HIGH);
  }

  if(digitalRead(7))
  {
    digitalWrite(yLED,LOW);
  }
  else
  {
    digitalWrite(yLED,HIGH.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         );
  }
  
}
