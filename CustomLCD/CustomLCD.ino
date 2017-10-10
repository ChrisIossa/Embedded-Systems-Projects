#define Epin 8
#define RSpin 7
#define D4pin 9
#define D5pin 10
#define D6pin 11
#define D7pin 12
byte dataPins[4] ={D4pin, D5pin, D6pin, D7pin};

void setup() {
  // put your setup code here, to run once:
  for (int i=7;i<=12;i++)
  {
    pinMode(i,OUTPUT);
  }
  digitalWrite(Epin, LOW);
  digitalWrite(RSpin, LOW);
  initalize();
  sendByte(0x28);
  sendByte(0x0C);
  sendByte(0x06);
  sendByte(0x01);
  delay(3);
  writeStr("Hello");
  sendByte(0x80|0x40);
  writeStr("World");
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void initalize()
{
  delay(15);
  writeFourBits(0x03);
  delay(5);
  writeFourBits(0x03);
  delayMicroseconds(100);
  writeFourBits(0x03);
  writeFourBits(0x02);
}

void writeFourBits(byte val)
{
  for(int i=0; i<4; i++)
  {
    if(val&0x01)
    {
      digitalWrite(dataPins[i],HIGH);
    }
    else
    {
      digitalWrite(dataPins[i],LOW);
    }
    val>>=1;
  }
  digitalWrite(Epin, HIGH);
  digitalWrite(Epin,LOW);
  delayMicroseconds(100);
  
}

void sendByte(byte val)
{
  digitalWrite(RSpin,LOW);
  writeFourBits(val>>4);
  writeFourBits(val);
  
}

void sendChar(byte val)
{
  digitalWrite(RSpin,HIGH);
  writeFourBits(val>>4);
  writeFourBits(val);
}

void writeStr(char* str)
{
 while (*str)
 {
  sendChar(*str);
  str++;
 }
}



