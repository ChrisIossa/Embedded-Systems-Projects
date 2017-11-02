#include <LiquidCrystal_I2C.h>

#include <Wire.h>


/*
 * Create an object to interact with the display
 * the arguments are the I2C address
 * the number of chars per line
 * and the number of lines respectively

 */
LiquidCrystal_I2C lcd(0x38, 16,2);
void setup() {
  // put your setup code here, to run once:

  //initalize the 1602 display
  lcd.init();

  //turn the backlighting on
  lcd.setBacklight(HIGH);

  //print a greeting
  lcd.print("Hello From I2C");
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //set the cursor to the desired column and row
  //in the present case the first char of the second row
  lcd.setCursor(0,1);
  lcd.print( millis());
}
