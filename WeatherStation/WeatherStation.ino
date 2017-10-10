
#define Epin 8
#define RSpin 7
#define D4pin 9
#define D5pin 10
#define D6pin 11
#define D7pin 12
#define D2pin 2
byte dataPins[4] ={D4pin, D5pin, D6pin, D7pin};
const int maxTime = 1600;

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
 }

void loop() {
  // put your main code here, to run repeatedly:
  float humid =0;
  float temp = 0;
  char* tempStr;
  delay(2000);
  readDHT(&temp, &humid);
  sendByte(0x80|0x00);
  writeStr("Temp: ");
  sendByte(0x80|0x07);
  writeStr(String( (int) temp).c_str());
  sendByte(0x80|(String( (int) temp)).length()+7);
  sendChar(0xDF);
  sendByte(0x80|(String( (int) temp)).length()+8);
  writeStr("F");
  sendByte(0x80|0x40);
  writeStr("Humid: ");
  sendByte(0x80|0x47);
  writeStr(String((int)humid).c_str());
  sendByte(0x80|0x4A);
  writeStr("%");
}

int readState (boolean val)
 {
  pinMode(D2pin, INPUT_PULLUP);
  int count = 0;
  while(true)
  {
    if( (digitalRead(2)==val ) && (count<=maxTime))
    {
      count++;
    }
    
    else if(count>maxTime)
    {
    return 0;
    }
    
    else
    {
      return count;
    }
  }
}

boolean readDHT(float *temp, float *humid)
{
  int readArr[80];
  
  pinMode(D2pin, OUTPUT);
  digitalWrite(D2pin, LOW);
  delay(18);
  digitalWrite(D2pin, HIGH);
  delayMicroseconds(40);
  
  pinMode(D2pin,INPUT_PULLUP);
  delayMicroseconds(10);
  
  int readLow=readState(LOW);
  int readHigh=readState(HIGH);
  
  if(readLow==0 || readHigh==0)
  {
    return false;
  }
  
  for(int i=0; i<40; i++)
  {
    readArr[2*i]=readState(LOW);
    readArr[2*i+1]=readState(HIGH);
  }

  byte highHumid = reassembleByte(readArr,0);
  byte lowHumid = reassembleByte(readArr,8);

  byte highTemp = reassembleByte(readArr,16);
  byte lowTemp = reassembleByte(readArr,24);

  byte checksum = reassembleByte(readArr,32);

  if(checksum != (highHumid+lowHumid+highTemp+lowTemp) )
  {
    return false;
  }
  else
  {
   *humid = (float) highHumid;
   *temp = (float) (highTemp*1.8+32); 
  }
}

byte reassembleByte(int* arrayIn, int iStart)
{
  byte value=0;
  for(int i = iStart; i<(iStart+8); i++)
  {
    value <<= 1;
    if(arrayIn[2*i+1] > arrayIn[2*i])
    {
      value |= 0x01;
    }
  }
  return value;
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



