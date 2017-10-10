void setup() 
{
  for( int i = 0; i < 8; i++ )
  {
    pinMode( i, OUTPUT );
  }

}
byte pinToSet = 0;
void loop() 
{
  digitalWrite( pinToSet, HIGH );
  delay( 40 );
  digitalWrite( pinToSet, LOW );
  delay( 40 );
  pinToSet++;
  pinToSet %= 8;
  
}
