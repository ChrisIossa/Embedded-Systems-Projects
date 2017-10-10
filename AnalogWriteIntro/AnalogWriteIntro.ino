#define D5 5
#define D6 6

void setup() {
  // put your setup code here, to run once:
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<255;i++)
  {
  analogWrite(D5,i);
  analogWrite(D6,255-i);
  delay(5);
    
  }
  for(int i=0;i<255;i++)
  {
  analogWrite(D5,255-i);
  analogWrite(D6,i);
  delay(5);
    
  }
 }

