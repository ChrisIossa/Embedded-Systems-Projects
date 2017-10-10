// Include the AdaFruit DHT library
#include <DHT.h>

// Define the pin we are using and the device type
#define DHTPin 2
#define DHTType DHT11

// Create our dht access object
DHT dht( DHTPin, DHTType );

void setup()
{
  // Initialize the Serial package and ...
  Serial.begin( 9600 );

  // ... the DHT library
  dht.begin();

  // Print a greeting.
  Serial.println( "DHT11 starting up!" );
}

// This method gets called repeatedly
void loop() 
{
  // Sleep for 2 seconds.  The DHT can only be read every
  // 2 seconds anyway.
  delay( 2000 );

  // Get the temperature in Farenheit and the relative humidity
  float tempF    = dht.readTemperature( true );
  float humidity = dht.readHumidity();

  // Check that nothing went wrong.
  if( isnan( tempF ) | isnan( humidity ) )
  {
    Serial.println( "Could not read DHT11!" );
    return;
  }

  // Print out the result.
  Serial.print( "Humidity: " );
  Serial.print( humidity );
  Serial.print( "%\t Temperature(F): ");
  Serial.println( tempF ); 
  

}
