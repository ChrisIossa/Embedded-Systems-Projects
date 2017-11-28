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
byte segmentMapping[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };

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

