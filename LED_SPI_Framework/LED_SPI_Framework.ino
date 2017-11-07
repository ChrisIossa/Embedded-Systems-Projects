#include <SPI.h>

// Define which pin we will be using for the Chip Selection
#define SPISelectPin 10


void setup()
{
  SPI.begin();
  SPI.setBitOrder( MSBFIRST );
  pinMode( SPISelectPin, OUTPUT );
}

byte currentValue = 0;
byte segmentMapping[] = { Your values go here! };

void loop()
{
  updateShiftRegister( segmentMapping[ currentValue ] );
  currentValue = ( ++currentValue ) %16;
  delay( 1000 );
}

void updateShiftRegister( byte value )
{
  digitalWrite( SPISelectPin, LOW );
  SPI.transfer( value );
  digitalWrite( SPISelectPin, HIGH );
}

