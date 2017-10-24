//SimpleCompareOutputMode.ino
//Simple example of change output values using 
//compare register mode

#define redPin 9
#define bluePin 10




void setup() {
  // put your setup code here, to run once:

  //both pins need to be outputs
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //initialize timer 1
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  //set the prescalar to 256
  TCCR1B |= _BV(CS12);
  
  //the waveform generation is just "normal", that ius the WGM bits are all zero
  //Set the "compare output mode" to "toggle"

  TCCR1A |= _BV(COM1A0) | _BV(COM1B0);
  OCR1A = 16384; // == 2^16 /4
  OCR1B = 49152; // 3/4 * 2^16
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
