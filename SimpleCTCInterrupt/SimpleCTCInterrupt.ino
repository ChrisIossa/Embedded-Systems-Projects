//Simple example "CTC" (Clear Timer on Compare Match) Interrupts

#define LEDPin 5

void setup() {
  // put your setup code here, to run once:

  pinMode(LEDPin, OUTPUT);

  //initalize timer 1
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

   //set the prescaler to 256
   TCCR1B |= _BV (CS12);

   //set the wave generation to CTC -- "Clear Timer on compare match"

   TCCR1B |= _BV( WGM12 );

   //enable timer compare interrupt
   TIMSK1 = _BV (OCIE1A);

   //this the compare value = half the maximum value
   OCR1A = 31256;

   //turn interrupts back on
   interrupts();
   

}

void loop() {
  // put your main code here, to run repeatedly:

}

ISR (TIMER1_COMPA_vect)
{
  digitalWrite(LEDPin, !digitalRead(LEDPin));
}

