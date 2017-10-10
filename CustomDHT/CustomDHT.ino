#define D2 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 float humid =0;
 float temp = 0;
 delay(2000);
 readDHT(&temp, &humid);
 Serial.print("Temperature: ");
 Serial.print(temp);
 Serial.println("°C");
 Serial.print("Humidity: ");
 Serial.print(humid);
 Serial.println("");
 
}

const int maxTime = 1600;


int readState (boolean val)
 {
  pinMode(D2, INPUT_PULLUP);
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
  
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  delay(18);
  digitalWrite(D2, HIGH);
  delayMicroseconds(40);
  
  pinMode(D2,INPUT_PULLUP);
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
   *temp = (float) highTemp; 
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

  


