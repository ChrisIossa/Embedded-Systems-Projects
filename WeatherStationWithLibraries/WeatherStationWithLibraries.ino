#include <LCD.h>
#include <Temp.h>
void setup() {
  // put your setup code here, to run once:
  
  
 }

LCD LCDScr(8,7,9,10,11,12);
Temp DH11(2);
void loop() {
  // put your main code here, to run repeatedly:
  float humid =0;
  float temp = 0;
  char* tempStr;
  delay(2000);
  DH11.readDHT(&temp, &humid);
  LCDScr.sendByte(0x80|0x00);
  LCDScr.writeStr("Temp: ");
  LCDScr.sendByte(0x80|0x07);
  LCDScr.writeStr(String( (int) temp).c_str());
  LCDScr.sendByte(0x80|(String( (int) temp)).length()+7);
  LCDScr.sendChar(0xDF);
  LCDScr.sendByte(0x80|(String( (int) temp)).length()+8);
  LCDScr.writeStr("F");
  LCDScr.sendByte(0x80|0x40);
  LCDScr.writeStr("Humid: ");
  LCDScr.sendByte(0x80|0x47);
  LCDScr.writeStr(String((int)humid).c_str());
  LCRScr.sendByte(0x80|0x4A);
  LCDScr.writeStr("%");
}
