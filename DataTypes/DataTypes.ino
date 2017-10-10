volatile byte a = 10;
volatile byte b = 20;

void setup() {
  // put your setup code here, to run once:
  //initalize the Serial system
  Serial.begin(9600);

  //We'll repeat the measurement this many times
  volatile uint8_t counter = 255;
  //get the starting time
  unsigned long startTime = micros();

  //assembly language loop invoking our instruction

  asm 
  (
    "lds r24, (a) \n"  //Load the value in a into register r24
    "lds r26, (b) \n"   //Load the value of b into register r26
    "1:          \n"   //This is the target of our loop
    "mul r26,r24 \n"   //our testing code goes here
    "dec %0      \n"   //decrement the loop counter
    "brne 1b     \n"   //jump back o the target if the counter is not zero
    : : "r" (counter): "r24", "r26"
  );
    //get the end time
    unsigned long endTime = micros();

    //now compute the elapsed time and ...
    unsigned long elapsedTime= endTime - startTime;

    //...report it
    Serial.print( "Elapsed time ");
    Serial.print(elapsedTime);
    Serial.println( " microseconds");
}

//keep the linker happy
void loop() {
  // put your main code here, to run repeatedly:

}
