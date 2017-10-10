void setup() 
{
  DDRD=0xFF;
  
}
//byte pinToSet = 0;
byte num=0;

void loop() 
{
  PORTD=num;
  delay(720);
  //Serial.println("Num = " +num);
  num++;
}
