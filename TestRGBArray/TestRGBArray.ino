#include <RGB.h>

#define RGBPin 2

float redArray[]   = { 179.294, 179.294, 179.294, 160.948, 107.294, 53.647, 35.294, 35.294, 35.294, 35.294, 35.294, 53.647, 107.294, 160.941, 179.294, 179.294 };
float blueArray[]  = {   9.804,  24.706,  40.000,  49.804,  49.804, 49.804, 49.804, 49.804, 49.804, 34.902, 19.608,  9.804,   9.804,   9.804,   8.804,   9.804 };
float greenArray[] = {   9.804,   8.804,   8.804,   9.804,   9.804,  9.804, 19.608, 34.902, 49.804, 49.804, 49.804, 49.804,  49.804,  49.804,  40.000,  24.706 }; 
int delayVal = 75;

RGB rgb( RGBPin, 16 );
void setup() 
{
  rgb.clear();
}

int loopIndex = 0;
void loop() 
{
  for(int i = 0; i < 16; i++ )
  {
    rgb.clear();
    int index = ( i + loopIndex ) % 16;
    float redValue   = redArray[ index ];
    float greenValue = greenArray[ index ];
    float blueValue  = blueArray[ index ];
    rgb.setColor( i, greenValue, redValue, blueValue );
    rgb.show();
    delay( delayVal );
  }
  loopIndex = (loopIndex + 1) % 16;
}
