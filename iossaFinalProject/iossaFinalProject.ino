#include <LiquidCrystal.h>
#include <RGB.h>

#define RGBPin 3
#define numPixels 1
#define leftBtn 6
#define rightBtn 3
RGB rgb( RGBPin, numPixels );

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // put your setup code here, to run once:
  rgb.setColor(0, 0, 0, 0);
  rgb.show();
  lcd.begin(16, 2);

  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Tic-Tac-Toe");

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Left btn: OK");
  lcd.setCursor(0, 1);
  lcd.print("Right btn: Menu");

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Instructions:");
  lcd.setCursor(0, 1);
  lcd.print("X is Green");
  rgb.setColor(0, 0, 255, 0);
  rgb.show();


  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Instructions:");
  lcd.setCursor(0, 1);
  lcd.print("O is Red");
  rgb.setColor(0, 255, 0, 0);
  rgb.show();

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Instructions:");
  lcd.setCursor(0, 1);
  lcd.print("Yellow is free");
  rgb.setColor(0, 255, 223, 0);
  rgb.show();

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Instructions:");
  lcd.setCursor(0, 1);
  lcd.print("Off is NA");
  rgb.setColor(0, 0, 0, 0);
  rgb.show();

  delay(3000);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Use the joystick");
  lcd.setCursor(0, 1);
  lcd.print("to select");
  printMenu();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void printMenu()
{

  bool choiceMade = false;
  bool deadSet = true;
  while (!choiceMade)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Dead Zone");
    lcd.setCursor(0, 1);
    lcd.print("Reset Score");
    delay(500);
    if (deadSet)
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Reset Score");

    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Dead Zone");
    }
    if(digitalRead(leftBtn))
    {
      choiceMade=true;
    }
    if(digitalRead(rightBtn))
    {
      deadSet=!deadSet;
    }
    
  }

}


