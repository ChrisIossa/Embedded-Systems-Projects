
void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(4,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte state = digitalRead(4);
  if(state==0)
  {
    digitalWrite(9);
  }
  }
}
