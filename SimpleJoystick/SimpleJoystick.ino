void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("X: ");
  Serial.println((int)  + analogRead(2));
  Serial.print("Y: "); 
  Serial.println((int)analogRead(3));
  Serial.println();
  delay(1000);
}
