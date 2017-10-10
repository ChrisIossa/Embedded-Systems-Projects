#include <LEDS.h>

LEDS leds(6,5);
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i=0; i<100; i+=10)
  {
  leds.setRedLevel(i);
  leds.setGreenLevel(100 -i);
  delay (100);
  }

  
  for (int i=0; i<100; i-=10)
  {
  leds.setRedLevel(i);
  leds.setGreenLevel(100 -i);
  delay (100);
  }
}
