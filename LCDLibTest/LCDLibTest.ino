#include <LCD.h>
LCD LCDScr(8,7,9,10,11,12);
void setup() {
  // put your setup code here, to run once:
LCDScr.startScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  LCDScr.sendByte(0x80|0x00);
  LCDScr.writeStr("Temp: ");
}
