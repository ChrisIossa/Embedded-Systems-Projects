#include <RGB.h>

#define RGBPin 3
#define numPixels 1

RGB rgb( RGBPin, numPixels );
void setup() 
{
  rgb.clear();

  // Note the LED arrays actually use GRB !
  rgb.setColor( 0, 0, 255, 0 );

  // Uncomnent this line when there are two devices
  //rgb.setColor( 1, 255, 0, 60 );
  
  rgb.show();
}
int rVal=0;
int gVal=0;
int bVal=0;
int colOp=0;
void loop() 
{
  
    
  int newRVal=random(0,255);
  int newGVal=random(0,255);
  int newBVal=random(0,255);
  while(rVal!=newRVal && gVal!=newGVal && bVal!=newBVal)
  {
    rgb.clear();
    if(newRVal>rVal)
    {
      rVal++;
    }
    else if(newRVal==rVal)
    {
      //null
    }
    else
    {
      rVal--;
    }

    if(newBVal>bVal)
    {
      bVal++;
    }
    else if(newBVal==bVal)
    {
      //null
    }
    else
    {
      bVal--;
    }

    if(newGVal>gVal)
    {
      gVal++;
    }
    else if(newGVal==gVal)
    {
      //null
    }
    else
    {
      gVal--;
    }
  rgb.setColor( 0, rVal, gVal , bVal );
  //rgb.setColor( 1, gVal, bVal , rVal );
  rgb.show();
  delay(5);
  }

  

}
