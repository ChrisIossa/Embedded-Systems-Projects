#include <Servo.h>


int enablePin = 11; //enable pin for IC
int in1Pin = 3; //DC motor 
int in2Pin = 5; //DC motor
//int servoRot=90; //angle of the servo motor //depricated
Servo myMotor; //motor object to represent servo

void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  myMotor.attach(8); //attach servo to pin 8
  myMotor.write(90);
  //Serial.begin(9600); //depricated
}

void loop() {
  // put your main code here, to run repeatedly:

  int stickValY = analogRead(3);
  int stickValX = analogRead(2);

  //move DC Motor
  if (stickValY >= 480 && stickValY <= 550)
  {
    setMotor(0, false);
  }
  else if (stickValY < 470)
  {
    setMotor(map(stickValY, 470, 0, 0, 255), true);
  }
  else
  {
    setMotor(map(stickValY, 550, 1023, 0, 255), false);
  }

  //Servo Motor
  if (stickValX >= 500 && stickValX <= 600)
  {
    myMotor.write(0);
  }
  else if (stickValX < 500)
  {
    myMotor.write(map(stickValX, 500, 0, 90, 1));
  }
  else
  {
    myMotor.write(map(stickValX, 600, 1023, 91, 180));
  }
  delay(10);
 
}


//Input parameters
//  Speed is a number between 0 and 255
//  reverse is either true or false
void setMotor(int speed, boolean reverse)
{
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, !reverse);
  digitalWrite(in2Pin, reverse);
}

