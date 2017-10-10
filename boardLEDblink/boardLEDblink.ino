void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int delayTime=500;
  digitalWrite(7, HIGH);
  delay(delayTime);
  digitalWrite(7,LOW);
  delay(delayTime);
}
