//SimpleSine.ino
//Simple Example of direct digital synthesis using fast PWM

#include <avr/interrupt.h>

#define TWOPI 6.283185
#define AMP 91
#define OFFSET 128

// the numerology above is 
// we choose the amplitude so that the resulting sine wave goes from
//0.7 to 4.3 with the center at 2.5 volts
// with these choices, the emitter follower stays in its linear region
// 91= (2.5 - 0.7) / 2.5 * 127

#define speakerPin 9

//setup the lookup table
#define TABLELENGTH 256
byte wave [TABLELENGTH];

void setup() {
  // put your setup code here, to run once:


  //load the lookup table
  float phaseAdvance = TWOPI/TABLELENGTH;
  for (int i=0; i<TABLELENGTH; i++)
  {
    float val = AMP * sin (phaseAdvance * 1);
    wave[i] = (byte) (val+OFFSET);
  }

  //make the speaker pin an output pin
  pinMode(speakerPin, OUTPUT);

  //set up timer 1 to do the PWM
  TCCR1B = _BV(CS10); //set the prescaler to 1
  TCCR1A |= _BV(COM1A1) | // the pin goes low when TCNT1 = OCR1A
            _BV(WGM10);
  TCCR1B != _BV(WGM12);

  //setupt timer2 to call the ISR periodically
  TCCR2A=0;
  TCCR2B = _BV(CS20); //set the prescaler to 1
  TIMSK2 = _BV(OCIE2A); //invoke interrupt handler when TCNNT2=OCRA2

  //this will set the freq
  OCR2A = 120;
  //make sure intterupts are enabled
  sei();
  }



void loop() {
  // put your main code here, to run repeatedly:

}

//interrput service routine
//this will be invoked each time TCNT2 = ORCA2
volatile byte index = 0;
ISR (TIMER2_COMPA_vect)
{
  //get the next valuen of the sample waveform
  OCR1AL = wave [index ++];

  //setting the counter to 48 accounts for all the instructions executed during the interrupt cycle
  TCNT2 =48;
}

