/*
 *  ____  _         _____             _____
 * |_   _(_) ___   |_   _|_ _  ___   |_   _|__   ___
 *   | | | |/ __|____| |/ _` |/ __|____| |/ _ \ / _ \
 *   | | | | (_|_____| | (_| | (_|_____| | (_) |  __/
 *   |_| |_|\___|    |_|\__,_|\___|    |_|\___/ \___|
 * 
 * Author: Chris Iossa
 * Board: Arduino Nano
 * Date: 11-30-2017
 * Class: CS298
 * Semester: Fall 2017
 * Professor: Dr. Coffman
 * 
 * Final Project:
 *    A two player (hotseat)
 *    Tic-Tac-Toe implementation
 *    for Arduino nano using:
 *       * an RGB array
 *       * Single RGB LED
 *       * LCD screen
 *       * two buttons
 *       * and an analog joystick
*/

//Headers
#include <LiquidCrystal.h> //needed for LCD screen
#include <RGB.h> //needed for RGB LED and RGB array

//Pin numbers
#define RGBPin 6 //pin of single LED
#define RGBArrPin 4 //pin of LED Array
#define leftBtn 3 //pin of leftBtn (ok)
#define rightBtn 2 //pin of rightBtn (reset)
#define joyX A3 //pin of Joystick X axis
#define joyY A2 //pin of Joystick Y axis

//RGB array segments (play area only)
#define topLeft 3
#define midLeft 2
#define lowLeft 1
#define topCen  4
#define midCen  5
#define lowCen  6
#define topRight 11
#define midRight 10
#define lowRight 9

/*
  values of board tied to each player
  x is green
  o is red
  because I originally reffered to the players by
  traditional Tic-Tac-Toe symbols
  rather than LED colors
*/
#define xPlayer -1
#define nullPlayer 0
#define oPlayer 1

#define joyTolerance 100 //space between the segments as determined by joystick location

RGB rgb( RGBPin, 1 ); //single LED
RGB rgbArr(RGBArrPin, 16); //rgb Array
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //lcd screen
int stickDeadX; //x coordinate of joystick center pos
int stickDeadY; //y coordinate of joystick center pos
int blinkSector;//sector which is currently selected (and should be blinking)

int board[] = {nullPlayer, nullPlayer, nullPlayer, nullPlayer, nullPlayer, nullPlayer, nullPlayer, nullPlayer, nullPlayer}; //value of each board segment
int lights[] = {topLeft, midLeft, lowLeft, topCen, midCen, lowCen, topRight, midRight, lowRight}; // the rgb array number corresponding to their board location

volatile bool ok = false; //bool used by ISR to indicate whether a selection has been made
volatile bool reset = false; //bool used by ISR to indicate whether the game is to be reset

bool isX = true; //bool to represent whose turn it is true when green, false when red. x is used because green was originally reffered to as X

int gWins = 0; // number of times green has won
int rWins = 0; // number of times red has won

void setup() {
  // put your setup code here, to run once:
  pinMode(leftBtn, INPUT_PULLUP);
  pinMode(rightBtn, INPUT_PULLUP);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(leftBtn, INPUT_PULLUP);
  pinMode(rightBtn, INPUT_PULLUP);
  rgb.setColor(0, 0, 0, 0);
  clearBoard();
  rgb.show();
  lcd.begin(16, 2);
  attachInterrupt(1, okPressed, RISING);
  attachInterrupt(0, resetPressed, RISING);
  printWelcome();
  zeroJoyStick();
  playGame();

}

void loop() {
}


/*
   Prints simple welcome message to signal boot up, and explain buttons
*/
void printWelcome()
{
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Tic-Tac-Toe");

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Left btn: OK");
  lcd.setCursor(0, 1);
  lcd.print("Right btn: Reset");
}

/*
   Sets the entire rgb array play area to a single color
*/

void colorBoard(int r, int g, int b)
{
  clearBoard();
  for (int i = 0; i < 9; i++)
  {
    rgbArr.setColor(lights[i], g, r, b);
  }
}

/*
   Resets board status and color to null
*/

void resetBoard()
{
  colorBoard(10, 5, 0);
  for (int i = 0; i < 9; i++)
  {
    board[i] = 0;
  }
  isX = true;
  rgb.setColor(0, 0, 100, 0);
  rgb.show();
}

/*
   Display a win message and flash the LED with the winners's color
   (Stalemate is handled as if null player won)
*/
void flashWin(int winner)
{
  lcd.clear();
  lcd.setCursor(0, 0);

  if (winner == xPlayer)
  {
    lcd.print("The Winner Is: ");
    lcd.setCursor(0, 1);
    lcd.print("Green!");
    for (int flashCount = 0; flashCount < 3; flashCount++)
    {
      for (int i = 25; i < 100; i++)
      {
        rgb.setColor(0, 0, i, 0);
        delay(10);
        rgb.show();
      }

      for (int i = 100; i > 25; i--)
      {
        rgb.setColor(0, 0, i, 0);
        delay(10);
        rgb.show();
      }
    }
  }
  else if (winner == nullPlayer)
  {
    lcd.print("Stalemate!");
    lcd.setCursor(0, 1);
    lcd.print("Try again");
    for (int flashCount = 0; flashCount < 7; flashCount++)
    {
      for (int i = 25; i > 0; i--)
      {
        rgb.setColor(0, 255, 255, i);
        delay(10);
        rgb.show();
      }

      for (int i = 0; i < 25; i++)
      {
        rgb.setColor(0, 255, 255, i);
        delay(10);
        rgb.show();
      }
    }
  }
  else
  {
    lcd.print("The Winner Is: ");
    lcd.setCursor(0, 1);
    lcd.print("Red!");
    for (int flashCount = 0; flashCount < 3; flashCount++)
    {
      for (int i = 25; i < 100; i++)
      {
        rgb.setColor(0, i, 0, 0);
        delay(10);
        rgb.show();
      }
      for (int i = 100; i > 25; i--)
      {
        rgb.setColor(0, i, 0, 0);
        delay(10);
        rgb.show();
      }
    }
  }
  resetBoard();
  printScore();
}

/*
   Prints the current scores for Red and Green, updated on win or reset
*/

void printScore()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Green:");
  lcd.setCursor(7, 0);
  lcd.print(gWins);
  lcd.setCursor(0, 1);
  lcd.print("Red  :");
  lcd.setCursor(7, 1);
  lcd.print(rWins);
}

/*
   Checks if the game has been won by summing the value of the cells in a given win scenario.
   If the sum is -3, green won (-1+-1+-1=-3)
 * * If the sum is 3, red won (1+1+1=3)
   also checks to see if the board is full, but no one has won (Stalemate)
   At the moment, the board does not detect no win scenarios until there are no remaining null cells
*/

void checkWin()
{
  int topSum, midSum, lowSum, leftSum, cenSum, rightSum, diagOneSum, diagTwoSum, nullCount = 0;

  topSum = getCellState(topLeft) + getCellState(topCen) + getCellState(topRight);
  midSum = getCellState(midLeft) + getCellState(midCen) + getCellState(midRight);
  lowSum = getCellState(lowLeft) + getCellState(lowCen) + getCellState(lowRight);
  leftSum = getCellState(topLeft) + getCellState(midLeft) + getCellState(lowLeft);
  cenSum = getCellState(topCen) + getCellState(midCen) + getCellState(lowCen);
  rightSum = getCellState(topRight) + getCellState(midRight) + getCellState(lowRight);
  diagOneSum = getCellState(lowLeft) + getCellState(midCen) + getCellState(topRight);
  diagTwoSum = getCellState(topLeft) + getCellState(midCen) + getCellState(lowRight);

  int winCases[] = {topSum, midSum, lowSum, leftSum, cenSum, rightSum, diagOneSum, diagTwoSum};

  for (int i = 0; i < 8; i++)
  {
    if (winCases[i] == -3)
    {
      gWins++;
      flashWin(xPlayer);
    }
    else if (winCases[i] == 3)
    {
      rWins++;
      flashWin(oPlayer);
    }
  }
  for (int i = 0; i < 9; i++)
  {
    if (board[i] == 0)
    {
      nullCount++;
    }
  }

  if (nullCount == 0)
  {
    flashWin(nullPlayer);
  }
}


/*
   Where the magic happens

   This function drives the whole game after initial setup
   The joystick position is read and used to determine which segment is being selected
   If segment is null, blinks segment until OK is detected
   at which point the cell is set to the current player's color

   If reset is detected, reset's board
   While loop is infinite
*/
void playGame()
{
  colorBoard(10, 5, 0);
  rgb.setColor(0, 0, 100, 0);
  rgb.show();
  isX = true;
  printScore();
  while (true)
  {
    int xPos = analogRead(joyX);
    int yPos = analogRead(joyY);
    if (yPos >= 0 && yPos <= (stickDeadY - joyTolerance)) //top
    {
      if (xPos <= 1024 && xPos >= (stickDeadX + joyTolerance)) //right
      {
        blinkSector = topRight;
      }
      else if (xPos <= (stickDeadX + joyTolerance) && xPos >= (stickDeadX - joyTolerance)) //center
      {
        blinkSector = topCen;
      }
      else //left
      {
        blinkSector = topLeft;
      }
    }
    else if (yPos <= (stickDeadY + joyTolerance) && yPos >= (stickDeadY - joyTolerance)) //middle
    {
      if (xPos <= 1024 && xPos >= (stickDeadX + joyTolerance)) //right
      {
        blinkSector = midRight;
      }
      else if (xPos <= (stickDeadX + joyTolerance) && xPos >= (stickDeadX - joyTolerance)) //center
      {
        blinkSector = midCen;
      }
      else //left
      {
        blinkSector = midLeft;
      }
    }
    else //low
    {
      if (xPos <= 1024 && xPos >= (stickDeadX + joyTolerance)) //right
      {
        blinkSector = lowRight;
      }
      else if (xPos <= (stickDeadX + joyTolerance) && xPos >= (stickDeadX - joyTolerance)) //center
      {
        blinkSector = lowCen;
      }
      else //left
      {
        blinkSector = lowLeft;
      }
    }
    blinkCell(isX);
    if (ok)
    {
      if (getCellState(blinkSector) == nullPlayer)
      {
        if (isX)
        {
          setCellState(blinkSector, xPlayer);
          rgbArr.setColor(blinkSector, 10, 0, 0);
          rgb.setColor(0, 100, 0, 0);

        }
        else
        {
          setCellState(blinkSector, oPlayer);
          rgbArr.setColor(blinkSector, 0, 10, 0);
          rgb.setColor(0, 0, 100, 0);
        }
        isX = !isX;
      }
      rgb.show();
      rgbArr.show();
      ok = false;
      checkWin();
    }
    if (reset)
    {
      reset = false;
      gWins = 0;
      rWins = 0;
      resetBoard();
      printScore();
    }
  }
}

/*
   Blinks a given cell in the play area, if isX is true, blinks green
   otherwise blinks red
*/
void blinkCell(bool isX)
{
  if (getCellState(blinkSector) == nullPlayer)
  {
    if (isX)
    {
      rgbArr.setColor(blinkSector, 10, 0, 0);
    }
    else
    {
      rgbArr.setColor(blinkSector, 0, 10, 0);
    }
    rgbArr.show();
    delay(750);
    rgbArr.setColor(blinkSector, 5, 10, 0);
    rgbArr.show();
    delay(750);
  }
}
/*
   Detects JoyStick deadzone
   as every joystick's deadzone is different
   asks the user to leave the joystick alone
   and takes the average position of the joystick over time
   (Based on Nintendo 64's joystick zeroing)
*/
void zeroJoyStick()
{
  int zeroXAggr = 0;
  int zeroYAggr = 0;
  int tries = 40;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Center JoyStick");
  lcd.setCursor(0, 1);
  delay(3000);
  for (int i = tries; i != 0; --i)
  {
    lcd.clear();
    zeroXAggr += analogRead(joyX);
    zeroYAggr += analogRead(joyY);
  }
  stickDeadX = (zeroXAggr / tries);
  stickDeadY = (zeroYAggr / tries);
  lcd.clear();
}

/*
   Turns off every light segment on RGB array
*/
void clearBoard()
{
  for (int i = 0; i < 16; i++)
  {
    rgbArr.setColor(i, 0, 0, 0);
  }
  rgbArr.show();
}

/*
   Returns the game state of a cell specified by parameter cell
*/
int getCellState(int cell)
{
  switch (cell)
  {
    case topLeft:
      return board[0];
    case midLeft:
      return board[1];
    case lowLeft:
      return board[2];
    case topCen:
      return board[3];
    case midCen:
      return board[4];
    case lowCen:
      return board[5];
    case topRight:
      return board[6];
    case midRight:
      return board[7];
    case lowRight:
      return board[8];
  }
}

/*
   Sets cell state of param cell to int val.
   Val is meant to be either xPlayer, nullPlayer, or oPlayer
*/
void setCellState(int cell, int val)
{
  switch (cell)
  {
    case topLeft:
      board[0] = val;
      break;
    case midLeft:
      board[1] = val;
      break;
    case lowLeft:
      board[2] = val;
      break;
    case topCen:
      board[3] = val;
      break;
    case midCen:
      board[4] = val;
      break;
    case lowCen:
      board[5] = val;
      break;
    case topRight:
      board[6] = val;
      break;
    case midRight:
      board[7] = val;
      break;
    case lowRight:
      board[8] = val;
      break;
  }
}
/*
   ISR to set ok bool when left button pressed
*/
void okPressed()
{
  ok = true;
}

/*
   ISR to set reset bool when right button pressed
*/
void resetPressed()
{
  reset = true;
}


//Unused functions from development period

/*
   Function to print cell state and light sector being checked
   was used during debugging to verify that lighting color matched stored state
*/

/*
  void printCellStates()
  {
  lcd.clear();
  for (int i = 0; i < 9; i++)
  {
    clearBoard();
    lcd.clear();
    lcd.setCursor(0, 0);
    switch (getCellState(lights[i]))
    {
      case xPlayer:
        lcd.print("Green");
        break;
      case nullPlayer:
        lcd.print("Null");
        break;
      case oPlayer:
        lcd.print("Red");
        break;
    }
    rgbArr.setColor(lights[i], 0, 10, 5);
    rgbArr.show();

    delay(1000);
  }
  }
  //*/

/*
   Function lights up each cell in the RGB array (not just the play area, all 16 segments)
   and prints their hardware number on the LCD
*/

/*
  void cycleBoard()
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++)
  {
    clearBoard();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(i);
    rgbArr.setColor(i, 0, 10, 5);
    rgbArr.show();
    delay(1000);
  }
  }
*/


