#define pin1A 9
#define pin2A 10

void setup() {
  // put your setup code here, to run once:
  pinMode(pin1A, OUTPUT);
  pinMode(pin2A, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<255;i++)
  {
  analogWrite(pin1A,i);
  analogWrite(pin2A,0);
  
    
  }
  for(int i=0;i<255;i++)
  {
  analogWrite(pin1A,0);
  analogWrite(pin2A,i);
  
    
  }
 }

