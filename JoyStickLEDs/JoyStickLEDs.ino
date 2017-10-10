#define D5 5
#define D6 6
#define D10 10
#define D11 11
void setup() {
  // put your setup code here, to run once:
 
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  analogWrite(D5,map(analogRead(2),0,1023,0,255));
  analogWrite(D6,map(analogRead(3),0,1023,0,255));
 
 
  }


