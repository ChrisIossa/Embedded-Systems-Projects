#define pin1A 9
#define pin2A 10


void setup() {
  // put your setup code here, to run once:
  pinMode(pin1A, OUTPUT);
  pinMode(pin2A, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  int stickVal=analogRead(2);
  if(stickVal>=500 && stickVal<=600)
  {
    analogWrite(pin1A,0);
    analogWrite(pin2A,0);
  }
  else if(stickVal<500)
  {
  analogWrite(pin1A,map(stickVal,500,0,0,255));
  analogWrite(pin2A,0);
  }
  else
  {

  analogWrite(pin1A,0);
  analogWrite(pin2A,map(stickVal,600,1023,0,255));
  }
 }

