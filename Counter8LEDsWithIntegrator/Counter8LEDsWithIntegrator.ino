/*
// Arduino NANO 
#define latchPin 5
#define clockPin 6
// */


// DigiSpark  */

int latchPin = 1;
int clockPin = 2;



void setup() 
{

  // Prepare the output pins for use
  pinMode( latchPin, OUTPUT );
  pinMode( clockPin, OUTPUT );

  // Always start with the latch bit clear and the clock bit set
  digitalWrite( latchPin, LOW );
  digitalWrite( clockPin, HIGH );
}

void loop() 
{
  // This is the value we are currently writing.
  byte value = 0;

  // This is our delay.  It will decrease after every 32 numbers.
  int delayMS = 64;

  do
  {

    // Write out the current value
    writeToShiftRegister( value );

    // Update the value
    value++;

    // Now decide how long to wait
    if( value % 32 == 0 ) 
    {
      delayMS /= 2;
    }
    delay( delayMS );
    
  } while( value > 0 );

  // Wait a bit at the very end so we can see that we are done.
  delay( 500 );
  
}

void writeToShiftRegister( byte val )
{
  // For the 74HC595, all the control signals are active high
  // Lower the latch --- Now it's "armed"
  digitalWrite( latchPin, LOW  );

  // We need to keep track of how many bits have already been written.
  byte bitCounter = 8;

  // Write out the data to shift register
  do
  {
    // The clock bit should be high. Lower it if we are writing a '0'
    if( ! ( val & 0x80 ) )
    {
      digitalWrite( clockPin, LOW );
    }

    // Now wait at least 3 RC time constants for the capacitor to charge or discharge if necessary
    delayMicroseconds( 9 );

    // Lower the clock bit to "arm" the clock and immediately raise it.
    //digitalWrite( clockPin, LOW  );
    //digitalWrite( clockPin, HIGH );
    asm
    (
      "cbi %0, %1 \n"
      "sbi %0, %1 \n"
      : : "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB2)     // Digispark
      //: : "I" (_SFR_IO_ADDR(PORTD)), "I" (PORTD6)   // Nano
      
    );

    // As promised, this leaves the clock bit high.
    
    // Shift the given value one place to the left and go on!
    val <<= 1;

    // This bit is done!
    bitCounter--;
    
  } while( bitCounter );

  // Now raise the latch so that our LEDs will see the new value
  digitalWrite( latchPin, HIGH );
}
