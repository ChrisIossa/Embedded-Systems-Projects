
/************************************************/
#include <Servo.h>
/************************************************/
Servo myservo;//create servo object to control a servo
#define ServoPin 8
/************************************************/
void setup()
{
  myservo.attach( ServoPin );//attachs the servo on pin 8 to servo object
  myservo.write(0);//back to 0 degrees 
  delay(1000);//wait for a second
}
/*************************************************/
void loop()
{  

/*  
  myservo.write(15);//goes to 15 degrees 
  delay(1000);//wait for a second
  myservo.write(30);//goes to 30 degrees 
  delay(1000);//wait for a second.33
  myservo.write(45);//goes to 45 degrees 
  delay(1000);//wait for a second.33
  myservo.write(60);//goes to 60 degrees 
  delay(1000);//wait for a second.33
  myservo.write(75);//goes to 75 degrees 
  delay(1000);//wait for a second.33
  myservo.write(90);//goes to 90 degrees
  delay(1000);//wait for a second
  myservo.write(75);//back to 75 degrees 
  delay(1000);//wait for a second.33
  myservo.write(60);//back to 60 degrees
  delay(1000);//wait for a second.33
  myservo.write(45);//back to 45 degrees
  delay(1000);//wait for a second.33
  myservo.write(30);//back to 30 degrees
  delay(1000);//wait for a second.33
  myservo.write(15);//back to 15 degrees 
  delay(1000);//wait for a second
  myservo.write(0);//back to 0 degrees 
  delay(1000);//wait for a second
  */
  
 // /*
  for(int i = 0; i < 180; i += 1 )
  {
    myservo.write( i );
    delay( 10 );
  }
  for( int i = 180; i > 0; i -= 1 )
  {
    myservo.write( i );
    delay( 10 );
  }
  //*/
}


