//Arduino Nano
/*
int latchPin = 5;
int clockPin = 6;
int dataPin = 4;
*/

//DigiSpark

  int latchPin = 1;
  int clockPin = 2;
  int dataPin = 0;
 

void setup() {
  // put your setup code here, to run once:
  pinMode( latchPin, OUTPUT);
  pinMode( dataPin, OUTPUT);
  pinMode( clockPin, OUTPUT);
}

byte value = 0;
void loop() {
  // put your main code here, to run repeatedly:
  //write the current value
  writeToShiftRegister (value);

  //update it and...
  value++;

  //wait a bit
  delay( 100 );
}

void writeToShiftRegister (byte val)
{
  //for the 74HC595 all the controls are active HIGH
  // lower the latch --- now it is armed
  digitalWrite (latchPin, LOW);
  
  //write out the value to the shift register
  shiftOut(dataPin, clockPin, MSBFIRST, val);

  //now raise the latch so that our LEDs will see the new value
  digitalWrite( latchPin, HIGH);
  
}

