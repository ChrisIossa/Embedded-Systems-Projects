//define the data type and the operation to be
//preformed
#define DATATYPE long
#define OPERATION i/j
 
void setup() {
  // put your setup code here, to run once:
  
  //initalize the Serial system
  Serial.begin(9600);
  //this operation will be repeated the square
  //of this number of times
  DATATYPE count=100;
  //this is the result of the calculation
  volatile DATATYPE z;

  //get the starting time 
  unsigned long t1= micros();

  //Perform the operation the required number of times
  for (DATATYPE i=0;i<count;i++)
  {
    for (DATATYPE j=0;j<count;j++)
    {
      z=OPERATION;
    }
  }

  //get the ending time
  unsigned long t2=micros();

  //compute the elapsed time and...
  unsigned long elapsedTime= t2-t1;

  //report it
  Serial.print ( "Elapsed time ");
  Serial.print (elapsedTime);
  Serial.println(" microseconds.");
}

//keep the linker happy
void loop() {
  // put your main code here, to run repeatedly:

}
