#include <RGB.h>

#define RGBPin 2

RGB rgb( RGBPin, 16 );

void setup() {
  // put your setup code here, to run once:
  rgb.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<5; i++)
  {
    if(i==0)
    {
      rgb.setColor( 7, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 8, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 1, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 9, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 10, random(0,255), random(0,255), random(0,255) );
      
    }
    else if (i==1)
    {
      rgb.setColor( 7, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 5, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 9, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 14, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 8, random(0,255), random(0,255), random(0,255) );
      
    }
    //finish later
    else if (i==2)
    {
      rgb.setColor( 10, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 14, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 15, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 8, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 7, random(0,255), random(0,255), random(0,255) );
      
    }
    else if (i==3)
    {
      rgb.setColor( 5, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 13, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 9, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 14, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 8, random(0,255), random(0,255), random(0,255) );
     }
     else
    {
      rgb.setColor( 6, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 8, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 15, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 14, random(0,255), random(0,255), random(0,255) );
      rgb.setColor( 13, random(0,255), random(0,255), random(0,255) );
     }
    rgb.show();
    delay(1000);
    rgb.clear();
  }
}
