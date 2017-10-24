//Simple example "TOV" (Timer Overflow) Interrupts

#define LEDPin 6

const static int startCount = 34286; //original 34286

void setup() {
  // put your setup code here, to run once:

  pinMode(LEDPin, OUTPUT);

  //initalize timer 1
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  

   //preload the counter with 65535 - 16MHZ / 256 / 2
   TCNT1 = startCount; //34286;
  
   //set the prescaler to 256
   TCCR1B |= _BV (CS12);

   //enable timer compare interrupt
   TIMSK1 = _BV (TOIE1);

   
   //turn interrupts back on
   interrupts();
   

}

void loop() {
  // put your main code here, to run repeatedly:

}

ISR (TIMER1_OVF_vect)
{
  digitalWrite(LEDPin, !digitalRead(LEDPin));
  TCNT1 = startCount; //34286;
}

