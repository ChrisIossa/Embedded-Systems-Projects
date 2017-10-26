// Example of PWM wave forming
#include <avr/interrupt.h>

#define PI2 6.283185
#define AMP 91
#define OFFSET 128

// Lookup table
#define LENGTH 256
byte wave[ LENGTH ];

// Define the waveforms
#define SINE     0
#define RAMP     1
#define TRIANGLE 2
#define SQUARE   3
#define RANDOM   4

#define speakerPin 9

void setup()
{


  int waveType = SINE;
  //int waveType = RAMP;
  //int waveType = TRIANGLE;
  //int waveType = SQUARE;
  //int waveType = RANDOM;


  switch( waveType )
  {
    case SINE:
      // Populate the wave table with a sine wave
      for( int i = 0; i < LENGTH; i++ )
      {
        float v = (AMP * sin( (PI2/LENGTH) * i ));
        wave[i] = byte( v + OFFSET );
      }
      break;

    case RAMP:
      // Populate the wave table with a ramp wave
      for( int i = 0; i < LENGTH; i++ )
      {
        wave[i] = i;
      }
      break;

    case TRIANGLE:
      // Populate the wave table with a triangle wave
      for( int i = 0; i < LENGTH; i++ )
      {
        if(  i < (LENGTH/2) )
        {
          wave[i] = i*2;
        }
        else
        {
          wave[i] = (LENGTH - 1) - (i*2);
        }
      }
      break;

    case SQUARE:
      // Populate the wave table with a square wave
      for( int i = 0; i < LENGTH; i++ )
      {
        if( i < (LENGTH/2) )
        {
          wave[i] = 255;
        }
        else
        {
          wave[i] = 0;
        }
      }
      break;

    case RANDOM:
      randomSeed[2];
      for( int i = 0; i < LENGTH; i++ )
      {
        wave[i] = random( 256 );
      }
      break;
  }

  // Make the speaker pin an output pin
  pinMode( speakerPin, OUTPUT );
  
  // Turn off interrupts
  noInterrupts();
 
  // Set up timer1 to do the PWM
  TCCR1B =  _BV( CS10 ); // Set the prescaler to 1
  TCCR1A |= _BV( COM1A1 ) | // The pin goes low when TCNT1 = OCR1A
            _BV( WGM10 );   // Use 8-bit fast PWM
  TCCR1B |= _BV( WGM12 ); 

  // Set up timer2 to call the ISR periodically
  TCCR2A = 0;
  TCCR2B = _BV( CS20 );   // Set the prescaler to 1
  TIMSK2 = _BV( OCIE2A ); // Invoke interrupt handler when TCNT2 = OCRA2

  // This will set the frequency
  OCR2A =  120;

  // Make sure interrupts are enabled
  interrupts();
}

void loop()
{
  // Keep the linker happy!
}

// Interrupt routine
volatile byte index = 0;
ISR( TIMER2_COMPA_vect )
{
  OCR1AL = wave[ index++ ];
  TCNT2 = 48;
}

