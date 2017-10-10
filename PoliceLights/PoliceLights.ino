void setup() 
{
  for( int i = 0; i < 8; i++ )
  {
    pinMode( i, OUTPUT );
  }

}

void loop() {
  // put your main code here, to run repeatedly:
   digitalWrite(1,HIGH);
   digitalWrite(5,HIGH);
   delay(120);
   digitalWrite(1,LOW);
   digitalWrite(5,LOW);
   digitalWrite(2,HIGH);
   digitalWrite(6,HIGH);
   delay(120);
   digitalWrite(2,LOW);
   digitalWrite(6,LOW);
   
   
}
