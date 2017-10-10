void setup() 
{
  //Serial.begin(9600);
  for( int i = 0; i < 8; i++ )
  {
    pinMode( i, OUTPUT );
  }
  
}
//byte pinToSet = 0;
byte num=0;

void loop() 
{
  byte mask=1;
  for (int i=0;i<8;i++)
  {
    if((num&mask)==0)
    {
      digitalWrite(i,LOW);
    }
    else
    {
      digitalWrite(i,HIGH);
    }
    mask<<=1;
  }
  delay(960);
  //Serial.println("Num = " +num);
  num++;
}
